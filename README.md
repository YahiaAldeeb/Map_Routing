# Map Routing - Shortest Path Algorithm

A C++ implementation of a shortest path routing system that finds the optimal route from a source to destination location, considering both walking and vehicle transportation with distance constraints.

## 📋 Problem Overview

This project solves a real-world transportation routing problem where a person can:
1. **Walk** from source location to a nearby intersection (max R meters)
2. **Ride a vehicle** through the road network at varying speeds
3. **Walk** from final intersection to destination (max R meters)

The system finds the path with minimum total travel time using graph algorithms and optimization techniques.

## 🏗️ System Architecture

### Core Components

- **Graph Construction**: Builds a weighted graph from intersection and road data
- **Distance Calculation**: Computes Euclidean distances between points
- **Node Filtering**: Identifies valid starting/ending intersections within walking range
- **Shortest Path**: Uses Dijkstra's algorithm with super nodes for optimal routing
- **Path Reconstruction**: Builds the final route from source to destination

### Key Features

- **Multi-modal Transport**: Combines walking (5 km/h) and vehicle speeds
- **Distance Constraints**: Respects maximum walking distance limitations
- **Optimized Performance**: Efficient algorithms for large-scale maps
- **Precise Output**: Results rounded to 2 decimal places

## 🚀 Performance Specifications

| Operation | Time Complexity | Description |
|-----------|----------------|-------------|
| Graph Construction | O(\|E\|) | Build adjacency list representation |
| Starting/Ending Nodes | O(\|V\|) | Find nodes within walking distance |
| Shortest Path | O(\|S\| \|E'\| log \|V'\|) | Dijkstra with multiple sources |
| Path Reconstruction | O(\|V'\|) | Build final route |

Where:
- |E| = Number of roads
- |V| = Number of intersections  
- |S| = Number of valid starting nodes
- |E'|, |V'| = Edges/vertices explored during search

## 📁 Project Structure

```
├── Map_Routing.h          # Header file with class definitions
├── Map_Routing.cpp        # Core routing algorithm implementation
├── Source.cpp             # Main program and I/O handling
├── NAMap.txt             # Map data (intersections and roads)
├── NAQueries.txt         # Query requests
└── outputNA.txt          # Generated results
```

## 🔧 Input Format

### Map File (`NAMap.txt`)
```
N                          # Number of intersections
ID1 X1 Y1                 # Intersection coordinates
ID2 X2 Y2
...
M                          # Number of roads
ID1 ID2 Length Speed       # Road connections with length (km) and speed (km/h)
...
```

### Query File (`NAQueries.txt`)
```
Q                          # Number of queries
SourceX SourceY DestX DestY R    # Source, destination coordinates and max walking distance (meters)
...
```

## 📤 Output Format

For each query:
```
0 3 4 5 2                  # Intersection path (space-separated IDs)
4.63 mins                  # Total travel time
1.72 km                    # Total distance
0.28 km                    # Walking distance
1.44 km                    # Vehicle distance
                          # Empty line

1 ms                       # Query processing time (excluding I/O)

5 ms                       # Total program execution time
```

## 🛠️ Compilation and Usage

### Prerequisites
- C++11 or later
- Standard Template Library (STL)

### Compilation
```bash
g++ -std=c++11 -O2 Source.cpp Map_Routing.cpp -o map_routing
```

### Execution
```bash
./map_routing
```

**Note**: Ensure `NAMap.txt` and `NAQueries.txt` are in the same directory.

## 🧮 Algorithm Details

### Super Node Technique
- Creates virtual **super source** connected to all valid starting intersections
- Creates virtual **super destination** connected to all valid ending intersections
- Enables single Dijkstra run instead of multiple source-destination pairs

### Distance Calculations
- **Euclidean Distance**: √[(x₁-x₂)² + (y₁-y₂)²]
- **Walking Time**: Distance / 5 km/h
- **Vehicle Time**: Distance / Road_Speed

### Optimization Features
- **Early Termination**: Stops when destination is reached
- **Distance Filtering**: Pre-filters unreachable nodes
- **Memory Efficient**: Uses adjacency list representation

## 📊 Test Cases

| Case Type | Intersections | Roads | Queries | Purpose |
|-----------|--------------|--------|---------|---------|
| Sample | ≤ 20 | ≤ 50 | ≤ 10 | Debugging |
| Medium | ≤ 20,000 | ≤ 25,000 | ≤ 1,000 | Performance Testing |
| Large | ≤ 200,000 | ≤ 250,000 | ≤ 1,000 | Scalability Testing |

## 🎯 Key Assumptions

- All roads are **bidirectional**
- Vehicle speeds are **constant** per road segment
- Walking speed is **fixed** at 5 km/h
- Vehicle boarding/alighting time is **negligible**
- Person uses **only one vehicle** for the entire journey

## 🔄 Potential Extensions

- **Variable Speed Handling**: Support for time-dependent road speeds
- **Map Visualization**: Graphical representation of routes
- **Multi-modal Options**: Support for different transport types
- **Real-time Updates**: Dynamic traffic condition integration

## 👨‍💻 Implementation Notes

- Uses `std::priority_queue` for Dijkstra's algorithm
- Implements custom `intersection` and `road` structures
- Handles edge cases like unreachable destinations
- Maintains precision with `std::fixed` and `std::setprecision`

## 📈 Performance Monitoring

The system tracks and reports:
- Query processing time (excluding I/O)
- Total program execution time (including I/O)
- Memory usage through efficient data structures

---

**Author**: Transportation Algorithms Team  
**Language**: C++  
**Algorithm**: Modified Dijkstra with Super Nodes  
**Application**: Urban Route Planning
