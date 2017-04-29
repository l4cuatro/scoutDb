
/*

Copyright 2017 [redacted]

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/

#include <string>

#include <iostream>

using namespace std;

namespace ScoutDb {

	class Team {
		
	public:

		unsigned short int teamIndex,
			matchesPer,
			matchesPlayed;
		
		unsigned short int* allies;
		unsigned short int* opponents;
			
		unsigned char record[3];
		
		unsigned char ap,
			wp;
		
		int sp;
		
		int allyScoreSum,
			oppScoreSum;

		double avgScored,
			avgScoredOn,
			scoreRatio;
		
		string number; //Team Number
		
		Team(string num, unsigned short int index, unsigned short int matchesPerTeam) { //Constructor
			matchesPer = matchesPerTeam;
			allies = (unsigned short int*)(malloc(matchesPerTeam * sizeof(unsigned short int)));
			opponents = (unsigned short int*)(malloc(2 * matchesPerTeam * sizeof(unsigned short int)));
			teamIndex = index;
			number = num;
			matchesPlayed = 0;
			sp = 0;
			ap = 0;
			allyScoreSum = 0;
			oppScoreSum = 0;
			avgScored = 0;
			avgScoredOn = 0;
			scoreRatio = 0;
			for(int i = 0; i < sizeof(record); i++)
				record[i] = 0;
			
			for(int i = 0; i < matchesPerTeam; i++) {
				allies[i] = 0;
				opponents[2 * i] = 0;
				opponents[2 * i + 1] = 0;
			}
		}

		void upStats(unsigned short int ally, unsigned short int opponent1, unsigned short int opponent2, bool bDidWinAuton, short int score, short int oppScore) {
			if (matchesPlayed < matchesPer) {
				allies[matchesPlayed] = ally;
				opponents[2 * matchesPlayed] = opponent1;
				opponents[2 * matchesPlayed + 1] = opponent2;
				if (score > oppScore) { //If a win
					record[0]++;
					sp += oppScore;
				}
				else if (score < oppScore) { //If a loss
					record[1]++;
					sp += score;
				}
				else { //If a tie
					record[2]++;
					sp += score;
				}
				allyScoreSum += score;
				oppScoreSum += oppScore;
				avgScored = allyScoreSum / (matchesPlayed + 1);
				avgScoredOn = oppScoreSum / (matchesPlayed + 1);
				if (avgScoredOn != 0)
					scoreRatio = avgScored / avgScoredOn;
				else
					scoreRatio = DBL_MAX;
				if (bDidWinAuton)
					ap++;
				wp = (2 * record[0]) + record[2]; // 2 WP for win, 1 WP for tie

				matchesPlayed++;

			}

			return;
		}
	
	};
	
}