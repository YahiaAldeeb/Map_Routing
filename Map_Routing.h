#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include <cmath>
#include <limits>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <unordered_map>
using namespace std;

struct intersection
{
    int id;
    double x;
    double y;
    double distToSource;
    double distToDestination;
    double time_source;// ma3mola bas 3shan mafdalsh a7sebha fy function solve query
    double time_destination;// ma3mola bas 3shan mafdalsh a7sebha fy function solve query
};

struct road
{
    int ray7_feen;
    double distance;
    double time;
};

class Map_Routing
{
public:
    int num_of_intersections;
    int num_of_roads;
    vector<intersection> intersections;
    vector<vector<road>> roads;
    vector<int> starts;
    vector<int> ends;
    const double walking_speed = 5.0; // km/h
    double total_time;
    double vehicle_dist;
    double total_walk;

    void bconstruct_elgraph(const string& filename); // awel objective et3mlt
    void e7sb_distances_le_cords_elquery(double sourceX, double sourceY, double destinationX, double destinationY);// 3shan yab2a saved distances akrnbyha 3alatoul
    void find_node_gowa_el_R(double R);// tany we talat objective et3mlt
    deque<int> dijkstra(double R);// rab3 objective et3mlt
    deque<int> final_final_final_path(const vector<int>& prev, int start, int end);//5ames objective et3malt


};