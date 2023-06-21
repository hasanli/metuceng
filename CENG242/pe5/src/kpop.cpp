#include "kpop.h"
#include "metal.h"
#include "rock.h"
#include "jazz.h"

int KPopBand::play(MusicBand *other)
{
    //auto* r = new auto(other);
    //r = MusicBand(other->get_name(), other->get_talent(), other->get_energy(), other->get_fan_count());
    double c = 0;
    if (dynamic_cast<KPopBand*>(other) != nullptr) {
       c = 2.0;
    }
    else {
        c = 0.5;
    }
    double score = ((this->get_fan_count()) + 0.1 * (this->get_talent()) * (this->get_energy())) * c;
    this->set_energy(this->get_energy() * 0.8);
    return score;
}

void KPopBand::rehearse(void) 
{
    this->set_energy(this->get_energy() - (0.5 * 0.2));
}