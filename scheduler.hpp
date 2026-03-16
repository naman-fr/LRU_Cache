#pragma once
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>

using Interval = std::pair<int,int>;

bool canAttendAll(std::vector<Interval> events)
{
    if(events.empty())
        return true;

    std::sort(events.begin(), events.end());

    int prev_end = events[0].second;

    for(size_t i=1;i<events.size();i++)
    {
        int start = events[i].first;

        if(start < prev_end)
            return false;

        prev_end = events[i].second;
    }

    return true;
}


int minRoomsRequired(std::vector<Interval> events)
{
    if(events.empty())
        return 0;

    std::sort(events.begin(), events.end());

    std::priority_queue<int,std::vector<int>,std::greater<int>> pq;

    int maxRooms = 0;

    for(auto &e : events)
    {
        int start = e.first;
        int end = e.second;

        while(!pq.empty() && pq.top() <= start)
            pq.pop();

        pq.push(end);

        maxRooms = std::max(maxRooms,(int)pq.size());
    }

    return maxRooms;
}


std::pair<int,std::vector<int>> assignRooms(std::vector<Interval> events)
{

    int n = events.size();

    std::vector<std::tuple<int,int,int>> ev;

    for(int i=0;i<n;i++)
        ev.push_back({events[i].first,events[i].second,i});

    std::sort(ev.begin(),ev.end());

    std::priority_queue<
        std::pair<int,int>,
        std::vector<std::pair<int,int>>,
        std::greater<std::pair<int,int>>
    > busy;

    std::priority_queue<int,std::vector<int>,std::greater<int>> freeRooms;

    std::vector<int> allocation(n);

    int nextRoom=0;

    for(auto &t:ev)
    {
        int start=std::get<0>(t);
        int end=std::get<1>(t);
        int index=std::get<2>(t);

        while(!busy.empty() && busy.top().first <= start)
        {
            freeRooms.push(busy.top().second);
            busy.pop();
        }

        int room;

        if(!freeRooms.empty())
        {
            room = freeRooms.top();
            freeRooms.pop();
        }
        else
        {
            room = nextRoom++;
        }

        allocation[index]=room;

        busy.push({end,room});
    }

    return {nextRoom,allocation};
}