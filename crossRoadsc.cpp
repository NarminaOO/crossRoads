#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <chrono>

std::mutex mutex;

void carArrived(std::vector<int>& carId, std::vector<int>& direction, std::vector<int>& time, const std::string& roads)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> guard(mutex);

        if (carId.empty())
            break;

        std::cout << "Traffic light on " << roads << " is green" << std::endl;
        auto it = carId.begin();
        auto it_d = direction.begin();
        auto it_t = time.begin();
        while (it != carId.end())
        {
            if ((roads == "road A" && *it_d <= 2) || (roads == "road B" && *it_d > 2))
            {
                std::cout << "Car " << *it << " passed in direction " << *it_d
                    << " at time " << *it_t << std::endl;
                it = carId.erase(it);
                it_d = direction.erase(it_d);
                it_t = time.erase(it_t);
            }
            else
            {
                ++it;
                ++it_d;
                ++it_t;
            }
        }
    }
}

int main()
{
    std::vector<int> carId = { 1, 3, 5, 2, 4 };
    std::vector<int> direction = { 2, 1, 2, 4, 3 };
    std::vector<int> time = { 10, 20, 30, 40, 40 };
    std::jthread thread_A(carArrived, std::ref(carId), std::ref(direction), std::ref(time), "road A");
    std::jthread thread_B(carArrived, std::ref(carId), std::ref(direction), std::ref(time), "road B");


    return 0;
}
