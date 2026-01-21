# K-Means Clustering in C++

This project is a C++ implementation of the **K-Means Clustering algorithm**. It was developed to demonstrate the core logic of unsupervised learning, specifically focusing on the iterative **Assignment** and **Update** steps using **Euclidean distance**.

The code is written in modern C++ (C++11/17 standards) using standard libraries only, ensuring portability and zero external dependencies.

## 🚀 Features

* **From Scratch Implementation:** No machine learning libraries used; pure logic implementation.
* **Modular Design:** The algorithm is broken down into helper functions (`assignmentStep`, `updateStep`) for readability and maintainability.
* **Euclidean Distance:** Standard distance metric implementation.
* **Convergence Check:** Automatically stops when centroids stabilize or max iterations are reached.

## 🛠️ Getting Started

### Prerequisites
You need a C++ compiler (like `g++`, `clang++`, or MSVC).

### How to Compile and Run

1.  **Clone the repository:**
    ```bash
    git clone [git@github.com:noraolofsson/k-means-clustering.git]

    cd k-means-clustering
    ```

2.  **Compile the code:**
    Using g++:
    ```bash
    g++ -o kmeans main.cpp -O3
    ```
    *(The `-O3` flag is optional but recommended for optimization)*

3.  **Run the executable:**
    ```bash
    ./kmeans
    ```

## 📂 Code Structure

The implementation is contained in a single file (`main.cpp`) for simplicity, but logically divided:

* `struct Point`: Represents 2D data points.
* `euclideanDistance()`: Calculates distance between points.
* `assignmentStep()`: Assigns each data point to the nearest centroid.
* `updateStep()`: Recalculates centroids based on the mean of assigned points.
* `kmeans()`: The main driver function managing the loop and convergence.
