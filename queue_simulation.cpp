#include <iostream>
using namespace std;
const int MAXSIZE = 100;

template <class T>
class Queue
{
    T entry[MAXSIZE];
    int Front, Rear, count;
public:

    Queue()
    {
        Front = 0;
        Rear = MAXSIZE - 1;
        count = 0;
    }

    bool empty()
    {
        return count == 0;
    }


    void push(T item)
    {
        if(!empty())
            return;

        Rear = (Rear + 1) % MAXSIZE;
        entry[Rear] = item;
        count++;
    }
    void pop()
    {
        if(empty())
            return;

        Front = (Front + 1) % MAXSIZE;
        count--;
    }

    T front()
    {
        return entry[Front];
    }
    int size()
    {
        return count;
    }
};

struct Customer
{
    int id;
    int arrivalTime;
    int itemIndex;
};

struct Item
{
    string name;
    int quantity;
    double price;};
void initializeItems(Item items[])
{
    items[0].name = "Item1";
    items[0].quantity = 10;
    items[0].price = 5;

    items[1].name = "Item2";
    items[1].quantity = 8;
    items[1].price = 7;

    items[2].name = "Item3";
    items[2].quantity = 12;
    items[2].price = 4;

    items[3].name = "Item4";
    items[3].quantity = 6;
    items[3].price = 10;
}

bool allItemsFinished(Item items[])
{
    for(int i = 0; i < 4; i++)
    {
        if(items[i].quantity > 0)
            return false;
    }
    return true;
}
void addCustomers(Queue<Customer>& q,int currentTime,int& nextID)
{
    int arrivals = rand() % 4;
    for(int i = 0; i < arrivals; i++)
    {
        Customer c;
        c.id = nextID++;
        c.arrivalTime = currentTime;
        c.itemIndex = rand() % 4;
        q.push(c);
    }}
void serveCustomer(Queue<Customer>& q,Item items[],int currentTime,int& servedCustomers,int& totalWaitingTime,int& longestWait,int& longestWaitCustomer,double& totalIncome, int& outOfStockCustomers)
{
    if(q.empty())
        return;
    Customer c = q.front();
    q.pop();
    int waitingTime = currentTime - c.arrivalTime;
    servedCustomers++;
    totalWaitingTime += waitingTime;
    if(waitingTime > longestWait)
    {
        longestWait = waitingTime;
        longestWaitCustomer = c.id;
    }
    int item = c.itemIndex;
    if(items[item].quantity > 0)
    {
        items[item].quantity--;
        totalIncome += items[item].price;
    }
    else
    {
        outOfStockCustomers++;
    }
}
int main()
{
    int N;
    cout << "Enter simulation time (minutes): ";
    cin >> N;
    Queue<Customer> q;
    Item items[4];
    initializeItems(items);
    int nextID = 1;
    int servedCustomers = 0;
    int totalWaitingTime = 0;
    int longestWait =0;
    int longestWaitCustomer = 0;
    double totalIncome = 0;
    int outOfStockCustomers = 0;
    for(int currentTime = 0;currentTime < N;currentTime++)
    {
        addCustomers( q,currentTime,nextID);
        serveCustomer(q, items, currentTime,servedCustomers,totalWaitingTime, longestWait, longestWaitCustomer,  totalIncome, outOfStockCustomers);
    }

    double averageWaitingTime = 0;

    if(servedCustomers > 0)
    {
        averageWaitingTime =  (double)totalWaitingTime / servedCustomers;
    }
    cout << "\n =Simulation Results =\n";
    cout << "Total Customers Served = "<< servedCustomers << endl;

    cout << "Total Waiting Time = "<< totalWaitingTime << endl;

    cout << "Average Waiting Time = "<< averageWaitingTime << endl;

    cout << "Customer With Longest Wait = Customer "<< longestWaitCustomer << endl;

    cout << "Longest Waiting Time = "<< longestWait << " minutes" << endl;

    cout << "Total Income = " << totalIncome << endl;
    
    cout << "Customers Who Could Not Buy = " << outOfStockCustomers << endl;
    
    int customersToEmptyStore = servedCustomers;
    int minutesNeeded = N;
    while(!allItemsFinished(items))
    {
        addCustomers( q, minutesNeeded, nextID);

        if(!q.empty())
        {
            customersToEmptyStore++;
        }

        serveCustomer(q,items,minutesNeeded,servedCustomers,totalWaitingTime,longestWait,longestWaitCustomer,totalIncome, outOfStockCustomers);

        minutesNeeded++;
    }

    cout << "\n= Empty Store Statistics =\n";

    cout << "Customers Needed To Empty Store = " << customersToEmptyStore << endl;

    cout << "Minutes Needed To Empty Store = "<< minutesNeeded << endl;

    return 0;
}