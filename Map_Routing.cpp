#include "Map_Routing.h"
#include <sstream>      
#include <iomanip>      
#include <limits>       
#include <algorithm>   
#include <stdexcept>   
#include <chrono>       
using namespace std;
using namespace std::chrono;

// el time complexity el mafrood O(E)
void Map_Routing::bconstruct_elgraph(const string& filename)
{
    ifstream efta7(filename);

    if (!efta7.is_open())
    {
        throw exception("el ragel mat");
    }

    efta7 >> num_of_intersections;

    intersections.resize(num_of_intersections);

    for (int i = 0; i < num_of_intersections; ++i)
    {
        int id;
        double x, y;
        efta7 >> id >> x >> y;
        intersections[id] = { id,x,y, 0, 0 ,0 ,0 };
    }

    efta7 >> num_of_roads;

    roads.resize(num_of_intersections+2);

    for (int i = 0; i < num_of_roads; ++i) {
        int u, v;
        double distance, speed;
        efta7 >> u >> v >> distance >> speed;
        double time = distance / speed;
        roads[u].emplace_back(road{ v, distance, time});
        roads[v].emplace_back(road{ u, distance, time});
    }

    efta7.close();

}
// hena el time complexity O(V)
void Map_Routing::e7sb_distances_le_cords_elquery(double sourceX, double sourceY, double destinationX, double destinationY) {
    for (auto& intermilan : intersections) {
        intermilan.distToSource = sqrt((intermilan.x - sourceX) * (intermilan.x - sourceX) + (intermilan.y - sourceY) * (intermilan.y - sourceY));
        intermilan.distToDestination = sqrt((intermilan.x - destinationX) * (intermilan.x - destinationX) + (intermilan.y - destinationY) * (intermilan.y - destinationY));
        intermilan.time_source = intermilan.distToSource / walking_speed;
        intermilan.time_destination = intermilan.distToDestination / walking_speed;
    }
}

// hena O(V) bardo
void Map_Routing::find_node_gowa_el_R(double R) {

    starts.clear();
    ends.clear();

    double R_km = R / 1000.0;

    for (const auto& inter : intersections) {
        if (inter.distToSource <= R_km) {
            starts.emplace_back(inter.id);
        }
        if (inter.distToDestination <= R_km) {
            ends.emplace_back(inter.id);
        }
    }
}
 // hena O(N) wel N dy 3ala 7aseb size el path
deque<int> Map_Routing::final_final_final_path(const vector<int>& prev, int start, int end) {

    //8yrtha le double-ended queue 3shan ma3lmsh reverse
    deque<int> path;

    for (int i = end; i != -1; i = prev[i]) {
        path.emplace_front(i);
    }

    // bt2akd men 7agat lawo path fady we lawo el path bad2a b3 7aga tanya 8er el super node
    if (path.empty() || path.front() != start) {
        return {};
    }

    // bashyl el two supernodes
    if (!path.empty() && path.front() == num_of_intersections) {
        path.pop_front();  // remove super_source
    }

    if (!path.empty() && path.back() == num_of_intersections + 1) {
        path.pop_back();  // remove super_dest
    }

    
    return path;
}

// hena O((E) log V)
deque<int> Map_Routing::dijkstra(double R) {

    this->total_time = 0;
    this->vehicle_dist = 0;
    this->total_walk = 0;

    find_node_gowa_el_R(R);
    if (starts.empty() || ends.empty()) return {};

    int super_source = num_of_intersections;
    int super_dest = num_of_intersections + 1;



    for (int start : starts) {
        roads[super_source].emplace_back(road{ start, intersections[start].distToSource, intersections[start].time_source });
    }

    for (int end : ends) {
        roads[end].emplace_back(road{ super_dest, intersections[end].distToDestination, intersections[end].time_destination });
    }

    vector<double> distance(num_of_intersections + 2, DBL_MAX);
    vector<int> feen_baba(num_of_intersections + 2, -1);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;

    distance[super_source] = 0.0;
    pq.emplace(0.0, super_source);

    while (!pq.empty()) {
        pair<double, int> top = pq.top();
        double current_dist = top.first;
        int node = top.second;
        pq.pop();

        if (node == super_dest) break;
        if (current_dist > distance[node]) continue;

        for (const auto& r : roads[node]) {
            double new_dist = current_dist + r.time;
            if (new_dist < distance[r.ray7_feen]) {
                distance[r.ray7_feen] = new_dist;
                feen_baba[r.ray7_feen] = node;
                pq.emplace(new_dist, r.ray7_feen);
            }
        }
    }


    roads[super_source].clear();
    for (int end : ends)
        roads[end].pop_back();


    return final_final_final_path(feen_baba, super_source, super_dest);
}
