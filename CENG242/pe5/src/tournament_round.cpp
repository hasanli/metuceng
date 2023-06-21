#include "tournament_round.h"

// TournamentRound functions goes here

TournamentRound::TournamentRound() { }
TournamentRound::TournamentRound(std::list<MusicBand*>_bands) {this->bands=bands;}
TournamentRound::TournamentRound(std::vector<MusicBand*>_bands) {
    std::list<MusicBand*> temp(_bands.begin(), _bands.end());
    this->bands= temp;
}

std::size_t TournamentRound::size() {return bands.size();}
   
//TournamentRound::TournamentRound(TournamentRound& other) { }
//TournamentRound::TournamentRound(TournamentRound&& other) { }
TournamentRound& TournamentRound::operator=(TournamentRound&& other) { return *this; }
TournamentRound& TournamentRound::get_next_round() {
        std::list<MusicBand*> winningBands;
        while (size() > 1) {
            MusicBand* band1 = bands.front();
            bands.pop_front();
            MusicBand* band2 = bands.back();
            bands.pop_back();
            int score1 = band1->play(band2);
            int score2 = band2->play(band1);
            if (score1 >= score2 || band2->get_energy() < 0) {
                int diff = score1 - score2;
                int change = (diff > band2->get_fan_count())? band2->get_fan_count() : diff;
                band1->set_fan_count(band1->get_fan_count() + change);
                band2->set_fan_count(band2->get_fan_count() - change);
                winningBands.push_back(band1);
            }
            if(score1 < score2 || band1->get_energy() < 0) {
                int diff = score2 - score1;
                int change = (diff > band1->get_fan_count())? band1->get_fan_count() : diff;
                band2->set_fan_count(band2->get_fan_count() + change);
                band1->set_fan_count(band1->get_fan_count() - change);
                winningBands.push_back(band2);
            }
        }
        if (size() == 1) {
            winningBands.push_back(bands.front());
            bands.pop_front();
        }
        bands = winningBands;
        return *this;
   
}

std::ostream& operator<< (std::ostream &os, TournamentRound &other) {
    for (auto it = other.bands.begin(); it != other.bands.end(); ++it) {
            os << (*it)->get_name();
            if (std::next(it) != other.bands.end()) {
                os << "\t";
            }
        }
    return os;
}