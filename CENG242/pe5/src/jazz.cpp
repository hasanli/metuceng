#include "kpop.h"
#include "metal.h"
#include "rock.h"
#include "jazz.h"



int JazzBand::play(MusicBand *other)
{
    //auto* r = new auto(other);
    //r = MusicBand(other->get_name(), other->get_talent(), other->get_energy(), other->get_fan_count());
    double c;
    if (dynamic_cast<KPopBand*>(other) != nullptr) {
        c = 0.5;
    }
    else if (dynamic_cast<MetalBand*>(other) != nullptr){
        c = 1.3;
    }
    else if (dynamic_cast<RockBand*>(other) != nullptr){
        c = 0.7;
    }
    else {
        c = 0.7;
    }
    double score = ((this->get_fan_count()) + 0.1 * (this->get_talent()) * (this->get_energy())) * c;
    this->set_energy(this->get_energy() * 0.94);
    return score;
}

void JazzBand::rehearse(void) 
{
    this->set_energy(this->get_energy() - (0.5 * 0.06));
    this->set_talent(this->get_talent() + 5);
}