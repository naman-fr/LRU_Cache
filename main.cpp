#include <iostream>
#include "lru_cache.hpp"
#include "scheduler.hpp"

int main()
{

    std::cout<<"------ LRU Cache Test ------"<<std::endl;

    LRUCache cache(3);

    cache.put(1,10);
    cache.put(2,20);
    cache.put(3,30);

    cache.printCache();

    std::cout<<"Get 1: "<<cache.get(1)<<std::endl;

    cache.put(4,40);

    cache.printCache();




    std::cout<<"\n------ Scheduler Test ------"<<std::endl;

    std::vector<Interval> events =
    {
        {9,10},
        {10,11},
        {11,12},
        {9,11}
    };

    if(canAttendAll(events))
        std::cout<<"Can attend all meetings"<<std::endl;
    else
        std::cout<<"Cannot attend all meetings"<<std::endl;



    std::cout<<"Minimum rooms required: "<<minRoomsRequired(events)<<std::endl;



    auto result = assignRooms(events);

    int rooms = result.first;
    std::vector<int> allocation = result.second;

    std::cout<<"Total rooms allocated: "<<rooms<<std::endl;

    for(int i=0;i<allocation.size();i++)
    {
        std::cout<<"Event "<<i<<" -> Room "<<allocation[i]<<std::endl;
    }

    return 0;
}