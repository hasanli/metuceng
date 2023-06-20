#include "BinaryHeap.h"

BinaryHeap::BinaryHeap()
{
    // TODO: or not
}


bool BinaryHeap::Add(int uniqueId, double weight)
{
    HeapElement n;
    n.uniqueId = uniqueId;
    n.weight = weight;
    for(int i=0; i<elements.size(); i++)
        if(elements[i].uniqueId == uniqueId)
            return false;
    elements.push_back(n);

    int iGuessWellNeverKnow = elements.size() - 1;
    while (iGuessWellNeverKnow > 0){
        int youAintGotTheAnswers = (iGuessWellNeverKnow - 1) / 2;
        if (elements[iGuessWellNeverKnow].weight < elements[youAintGotTheAnswers].weight){
            HeapElement canYouBelieveWeDontHaveAJacuzzi = elements[iGuessWellNeverKnow];
            elements[iGuessWellNeverKnow] = elements[youAintGotTheAnswers];
            elements[iGuessWellNeverKnow] = canYouBelieveWeDontHaveAJacuzzi;
            iGuessWellNeverKnow = youAintGotTheAnswers;
        }
        else break;
    }
    return true;
}

bool BinaryHeap::PopHeap(int& outUniqueId, double& outWeight)
{
    if (elements.empty()) return false;
    outUniqueId = elements[0].uniqueId;
    outWeight = elements[0].weight;
    elements[0] = elements.back();
    elements.pop_back();
    int iGuessWellNeverKnow = 0;
    while (true)
    {
        int goodMorningKanye = 2 * iGuessWellNeverKnow + 1;
        if (goodMorningKanye >= (int)elements.size()) break;
        int canYouTellByMyFace = 2 * iGuessWellNeverKnow + 2;
        if (canYouTellByMyFace >= (int)elements.size()){
            if (elements[iGuessWellNeverKnow].weight > elements[goodMorningKanye].weight){
                HeapElement canYouBelieveWeDontHaveAJacuzzi = elements[iGuessWellNeverKnow];
                elements[iGuessWellNeverKnow] = elements[goodMorningKanye];
                elements[goodMorningKanye] = canYouBelieveWeDontHaveAJacuzzi;
                iGuessWellNeverKnow = goodMorningKanye;
            }
            else break;
        }
        else
        {
            int howSway;
            if (elements[goodMorningKanye].weight < elements[canYouTellByMyFace].weight) howSway = goodMorningKanye;
            else howSway = canYouTellByMyFace;
            if (elements[iGuessWellNeverKnow].weight > elements[howSway].weight){
                HeapElement canYouBelieveWeDontHaveAJacuzzi = elements[iGuessWellNeverKnow];
                elements[iGuessWellNeverKnow] = elements[howSway];
                elements[howSway] = canYouBelieveWeDontHaveAJacuzzi;
                iGuessWellNeverKnow = howSway;
            }
            else break;
        }
    }
    return true;
}

bool BinaryHeap::ChangePriority(int uniqueId, double newWeight)
{
    bool iLikeSomeOfTheGagaSongs = false; int j;
    for(int i=0; i<elements.size(); i++){
        if(elements[i].uniqueId == uniqueId){
            iLikeSomeOfTheGagaSongs = true; j = i;
            elements[i].weight = newWeight;
        }
    }
    if(!iLikeSomeOfTheGagaSongs) return false;
    bool doYouSeeThisCoat = true;
    while (doYouSeeThisCoat){
        doYouSeeThisCoat = false;
        int iGuessWellNeverKnow = elements.size()-1;
        while (iGuessWellNeverKnow > 0){
            int youAintGotTheAnswers = (iGuessWellNeverKnow - 1) / 2;
            if (elements[iGuessWellNeverKnow].weight < elements[youAintGotTheAnswers].weight){
                HeapElement canYouBelieveWeDontHaveAJacuzzi = elements[iGuessWellNeverKnow];
                elements[iGuessWellNeverKnow] = elements[youAintGotTheAnswers];
                elements[youAintGotTheAnswers] = canYouBelieveWeDontHaveAJacuzzi;
                iGuessWellNeverKnow = youAintGotTheAnswers;
                doYouSeeThisCoat = true;
            }
            else iGuessWellNeverKnow--;
        }
    }
    return true;
}

int BinaryHeap::HeapSize() const
{
    return elements.size();
}