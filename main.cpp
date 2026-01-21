#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>

struct Point {
    double x, y;
};

struct KMeansResult {
    std::vector<Point> centroids;
    std::vector<int> assignments;
    int iterationsUsed;
};

double euclideanDistance(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

void assignmentStep(const std::vector<Point>& data, 
                    const std::vector<Point>& centroids, 
                    std::vector<int>& assignments) {
    
    for (size_t i = 0; i < data.size(); ++i) {
        double minDesc = std::numeric_limits<double>::max();
        int bestCluster = -1;

        for (size_t k = 0; k < centroids.size(); ++k) {
            double dist = euclideanDistance(data[i], centroids[k]);
            if (dist < minDesc) {
                minDesc = dist;
                bestCluster = k;
            }
        }
        assignments[i] = bestCluster;
    }
}

void updateStep(const std::vector<Point>& data, 
                const std::vector<int>& assignments, 
                std::vector<Point>& centroids) {
    
    size_t K = centroids.size();
    std::vector<Point> newSums(K, {0.0, 0.0});
    std::vector<int> counts(K, 0);

    for (size_t i = 0; i < data.size(); ++i) {
        int clusterId = assignments[i];
        newSums[clusterId].x += data[i].x;
        newSums[clusterId].y += data[i].y;
        counts[clusterId]++;
    }

    for (size_t k = 0; k < K; ++k) {
        if (counts[k] > 0) {
            centroids[k].x = newSums[k].x / counts[k];
            centroids[k].y = newSums[k].y / counts[k];
        }
    }
}

KMeansResult kmeans(const std::vector<Point>& data, int K, int maxIterations) {
    if (data.empty() || K <= 0) return {};

    std::vector<Point> centroids;
    for(int i = 0; i < K; ++i) {
        if(i < data.size()) centroids.push_back(data[i]);
        else centroids.push_back({0,0});
    }

    std::vector<int> assignments(data.size());
    int iter = 0;

    for (; iter < maxIterations; ++iter) {
        std::vector<Point> oldCentroids = centroids;

        assignmentStep(data, centroids, assignments);
        updateStep(data, assignments, centroids);

        // check convergens
        bool converged = true;
        for (size_t k = 0; k < K; ++k) {
            if (euclideanDistance(oldCentroids[k], centroids[k]) > 1e-6) {
                converged = false;
                break;
            }
        }

        if (converged) break;
    }

    return {centroids, assignments, iter};
}

int main() {
    std::vector<Point> data = {
        {1.0, 1.0}, {1.5, 2.0}, {3.0, 4.0}, 
        {10.0, 10.0}, {9.5, 9.8}, {10.5, 11.0}, 
        {20.0, 5.0}, {21.0, 4.0}, {20.5, 6.0}
    };

    int K = 3;
    
    std::cout << "K-means started..." << std::endl;
    KMeansResult result = kmeans(data, K, 100);

    std::cout << "Done after" << result.iterationsUsed << " iterations.\n\n";

    std::cout << "Centroids:\n";
    for (size_t k = 0; k < result.centroids.size(); ++k) {
        std::cout << "  Cluster " << k << ": (" 
                  << result.centroids[k].x << ", " 
                  << result.centroids[k].y << ")\n";
    }

    std::cout << "\nAssignments:\n";
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << "  Point (" << data[i].x << ", " << data[i].y 
                  << ") -> Cluster " << result.assignments[i] << "\n";
    }

    return 0;
}