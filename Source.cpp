#include "Map_Routing.h"
#include <sstream>      
#include <iomanip>      
#include <limits>       
#include <algorithm>   
#include <stdexcept>   
#include <chrono>   
using namespace std;
using namespace std::chrono;

int main() {
	//dah time el program kolo
	high_resolution_clock::time_point start = high_resolution_clock::now();

	Map_Routing  Mappppzzz;


	Mappppzzz.bconstruct_elgraph("NAMap.txt");


	int wa2t_el_queries = 0;
	int queries;
	double sourceX, sourceY;
	double destX, destY;
	double R;
	ifstream efta7;
	efta7.open("NAQueries.txt");

	ofstream etba3;
	etba3.open("outputNA.txt");



	if (efta7.is_open()) {
		efta7 >> queries;
		for (int i = 0; i < queries; i++) {
			efta7 >> sourceX >> sourceY >> destX >> destY;
			efta7 >> R;

			Mappppzzz.total_time = 0;
			Mappppzzz.vehicle_dist = 0;
			Mappppzzz.total_walk = 0;

			//time el queries bas
			high_resolution_clock::time_point query_start = high_resolution_clock::now();
			Mappppzzz.e7sb_distances_le_cords_elquery(sourceX, sourceY, destX, destY);
			deque<int> path = Mappppzzz.dijkstra(R);
			high_resolution_clock::time_point query_finish = high_resolution_clock::now();



			Mappppzzz.total_walk = Mappppzzz.intersections[path.front()].distToSource + Mappppzzz.intersections[path.back()].distToDestination;
			Mappppzzz.vehicle_dist = 0;
			Mappppzzz.total_time = (Mappppzzz.total_walk / Mappppzzz.walking_speed) * 60;

			for (size_t i = 0; i + 1 < path.size(); ++i) {
				int from = path[i];
				int to = path[i + 1];

				for (const auto& r : Mappppzzz.roads[from]) {
					if (r.ray7_feen == to) {
						Mappppzzz.vehicle_dist += r.distance;
						Mappppzzz.total_time += r.time * 60;
						break;
					}
				}
			}
			etba3 << fixed << setprecision(2);
			for (int i = 0; i < path.size() - 1; ++i)
			{
				etba3 << path[i] << " ";
			}
			etba3 << path.back();
			etba3 << endl;
			etba3 << fixed << Mappppzzz.total_time << " mins\n";
			etba3 << fixed << Mappppzzz.total_walk + Mappppzzz.vehicle_dist << " km\n";
			etba3 << fixed << Mappppzzz.total_walk << " km\n";
			etba3 << fixed << Mappppzzz.vehicle_dist << " km\n" << endl;


			wa2t_el_queries += duration_cast<milliseconds>(query_finish - query_start).count();
		}
		efta7.close();
		high_resolution_clock::time_point end = high_resolution_clock::now();
		int wa2t_el_program = duration_cast<milliseconds>(end - start).count();
		etba3 << wa2t_el_queries << " ms\n\n";
		etba3 << wa2t_el_program << " ms\n";
	}
	etba3.close();
	return 0;
}