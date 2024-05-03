## Cross Roads

This is a simple C++ program that simulates traffic on two roads. It demonstrates the usage of threads, mutexes, and vectors in C++.

![lt](https://github.com/NarminaOO/crossRoads/assets/149943881/4946f5d4-3d21-4e9a-99eb-9fb7226fa324)


## How it Works
The program defines a function `carArrived` which simulates cars arriving at traffic lights on two different roads (`road A` and `road B`). 
The cars have unique identifiers, directions, and arrival times. The function runs in separate threads for each road and processes the cars that arrive on that road.

- The program utilizes vectors to store information about cars, including their identifiers, directions, and arrival times.
- It uses mutexes to synchronize access to shared resources (the vectors) to prevent data races.
- Threads are used to simulate cars arriving concurrently on two different roads.

## Explanation of code 
```
std::mutex mutex;
```
Declares a mutex named `mutex`. Mutex is used to synchronize access to shared resources to prevent data races.


```
void carArrived(std::vector<int>& carId, std::vector<int>& direction, std::vector<int>& time, const std::string& roads)
```
Defines a function `carArrived` which takes references to three vectors (`carId`, `direction`, and `time`) representing car identifiers, their directions, and arrival times, respectively. 
It also takes a constant reference to a string `roads` representing the name of the road.

```
while (true)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::lock_guard<std::mutex> guard(mutex);
```
This initiates an infinite loop. Inside the loop, the thread sleeps for 1 second using `std::this_thread::sleep_for()` to simulate the passage of time. 
Then, it locks the mutex `mutex` using `std::lock_guard` to synchronize access to shared resources.

```
if (carId.empty())
    break;
```
Checks if the vector `carId` is empty. If it is, it breaks out of the loop, terminating the function.

```
std::cout << "Traffic light on " << roads << " is green" << std::endl;
```
Prints a message indicating that the traffic light on the specified road is green.

```
auto it = carId.begin();
auto it_d = direction.begin();
auto it_t = time.begin();
```
Declares iterators `it`, `it_d`, and `it_t` initialized to the beginning of the vectors `carId`, `direction`, and `time`, respectively.

```
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
```
Iterates through the vectors using the iterators. For each car, if its direction corresponds to the current road, it prints a message indicating the passage of the car and erases the corresponding entries from the vectors. 
Otherwise, it increments the iterators to move to the next car.

```
std::jthread thread_A(carArrived, std::ref(carId), std::ref(direction), std::ref(time), "road A");
std::jthread thread_B(carArrived, std::ref(carId), std::ref(direction), std::ref(time), "road B");
```
In the `main()` function, two threads (`thread_A` and `thread_B`) are created. Each thread calls the `carArrived` function with references to the same vectors `carId`, `direction`, and `time`, along with the name of the road as arguments. 
This simulates two roads with cars arriving on them concurrently. The `std::jthread` class is used for managing threads which automatically joins the threads upon destruction.
