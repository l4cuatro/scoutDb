/*
 * tourneyStats.hpp
 *
 *  Created on: Apr 5, 2017
 *      Author: Lentil
 */

using namespace std;

#ifndef TOURNEYSTATS_HPP_
#define TOURNEYSTATS_HPP_

#include <string>
#include <iostream>
#include "teamStatTracker.hpp"

namespace ScoutDb {

	class Tournament {
		Team* Teams;
		unsigned char matchesPerTeam;
		unsigned short int matchCt,
			teamCt;

		string input;


		Tournament(unsigned int matchCount, unsigned char teamCount) {
			Teams = (Team*)(malloc(teamCt * sizeof(Team)));
			matchCt = matchCount;
			teamCt = teamCount;
			matchesPerTeam = floor(4 * matchCt / teamCt);
			for (int i = 0; i < teamCt; i++) {
				cin >> input;
				Teams[i] = Team(input, i, matchesPerTeam);
			}
		}
	};
}




#endif /* TOURNEYSTATS_HPP_ */
