/*The project is on simulating an airport traffic control operation
 authors : Ghaida , Noura , Sara , Zahra */

#include <iostream>
#include<ctime>//for time to making the random numbers different after every execution
#include <cstdlib>//for rand() method, it return a postive numbers within the rasnge from 0.0 to RAND_MAX
using namespace std;
#define MAXP 5//the number of plans (array size)
void display(){
    
cout << "\n\t       *******                                 ";
cout << "\n\t        *      *                               ";
cout << "\n\t          *     *                              ";
cout << "\n\t        ***        *********************       ";
cout << "\n\t         *                              ****   ";
cout << "\n\t          *                             *****  ";
cout << "\n\t           *                                 * ";
cout << "\n\t            *                                * ";
cout << "\n\t           ***         ********      ********  ";
cout << "\n\t           *         *       *      *          ";
cout << "\n\t          *        *        *     *            ";
cout << "\n\t         **********        *     *             ";
cout << "\n\t                          *******              ";
cout << "\n \n";
}

struct plane{
    int timeArrive;//time of arrival in queue
}Plane;
 
struct circQueue{
    int countP;//number of airplanes in the queue
    int front;//front of the queue
    int rear;//rear of the queue
    plane data[MAXP];//the number of plane, ex: plane num 1 has this id .....
}Queue;

void initialQue(circQueue *que){ // to initialize queue at main
     
    que -> countP = 0;
    que -> front = -1;
    que -> rear = -1;
}
bool isEmpty(circQueue *que){ // to check whether the queue is empty or not
    
    if (que -> countP <= 0)
        return true;
    else
        return false;
}
bool isFull(circQueue *que){ // to check whether the queue is full or not
    
    if (que -> countP >= MAXP)
        return true;
    else
        return false;
}
void enQueue(circQueue *que , plane p){ // insert plane from the rear of the queue
    
        que -> countP ++;
        que -> rear = (que -> rear + 1) % MAXP;//ex : (-1 + 1) % 5 = 0
        que -> data[que -> rear] = p;
}
plane deQueue(circQueue *que){ // delete plane from the front of the queue
    
        que -> countP --;
        Plane = que -> data[que -> front];
        que -> front = ( que -> front + 1 ) % MAXP;//(0 + 1) % 5 = 1
    
    return Plane;
}

struct mangeAirport{
    
    circQueue landing; // variable to represent landing queue
    circQueue takeoff; // variable to represent taking off queue
    circQueue *planeLanding; // pointer for landing
    circQueue *planeTakeoff; // pointer for taking off
    float LandWait, TakeoffWait; // to calculate the total waiting time
    int numLand, numTakeoff; // number of requests that were accepted for landing or taking off
    int landed, tookoff, numPlanes, numRefuse;//number of planes landed, number of planes took off, number of planes processed, number of planes refused to use the runway
    int idle; // when there is no landing or takeoff on the Runway
    int curTime;//time for process(landing or take off )
    plane p;
};

void initialAirport(mangeAirport *a){
   
    initialQue(&(a -> landing));//landing now has countP, front and rear
    initialQue(&(a -> takeoff));//takeoff now has countP, front, and rear
    
    a -> planeLanding = &(a -> landing);//as a counter for the plane that landing
    a -> planeTakeoff = &(a -> takeoff);//as a counter for the plane that takeoff
    a -> LandWait = 0.0;
    a -> TakeoffWait = 0.0;
    a -> numLand = 0;
    a -> numTakeoff = 0;
    a -> landed = 0;
    a -> tookoff = 0;
    a -> numPlanes = 0;
    a -> numRefuse = 0;
    a -> idle = 0;
}
void newRecord(mangeAirport *a, int curTime){//make a new record for a plane
    a -> numPlanes ++;
    a -> p.timeArrive = curTime;
}

void succLand(mangeAirport *a, plane pl, int curtime ) // bring planes to successfully land
{
    int wait; // variable to calculate waiting time
    wait = curtime - pl.timeArrive; // Calculates the wait time by subtracting the current time from the time it entered the queue
    a -> landed ++;
    a -> LandWait += wait; // to calculate the total waiting time for landing planes
}

void succTookoff(mangeAirport *a, plane pl, int curtime ) // bring planes to take off
{
    int wait; // variable to calculate waiting time
    wait = curtime - pl.timeArrive; // Calculates the wait time by subtracting the current time from the time it entered the queue
    a -> tookoff ++;
    a -> TakeoffWait += wait; // to calculate the total waiting time for taking off planes
}
int airportIsEmpty(mangeAirport *a, int kind){//kind : 1 for land, 2 for takeoff

   if(kind==1)
   {
       return (isEmpty(a -> planeLanding));
   }
   else
   return (isEmpty(a -> planeTakeoff));

}
int airportIsFull(mangeAirport *a, int kind){//kind : 1 for land, 2 for takeoff

    if(kind==1)
   {
            return (isFull(a -> planeLanding));
    }
    else
    {
        return (isFull(a -> planeTakeoff));
        
    }
            
}
void airportEnQueue(mangeAirport *a, int kind){//kind : 1 for land, 2 for takeoff
    
   if(kind==1)
   {
         enQueue(a -> planeLanding, a -> p);
            a -> numLand ++;
       
   }
           
    else
    {
         enQueue(a -> planeTakeoff, a -> p);
         a -> numTakeoff ++;
            
        
    }
           
    
}
plane airportDeQueue(mangeAirport *a, int kind){//kind : 1 for land, 2 for takeoff

   if(kind==1)
   {
         Plane = deQueue(a -> planeLanding);
   }
   else
   {
          Plane = deQueue(a -> planeTakeoff);
   }

    return Plane;
}

void print(mangeAirport *a, int fRandom, int sRandom){ // function to print statistics
    cout << "Total number of planes processed " << a -> numPlanes << endl;
    cout << "Total number of planes accepted for landing " << a -> numLand << endl;
    cout << "Total number of planes accepted for taking off " << a -> numTakeoff << endl;
    cout << "Total number of planes refused " << a -> numRefuse << endl;
    cout << "Total number of planes successfully landed " << a -> landed << endl;
    cout << "Total number of planes successfully took off " << a -> tookoff << endl;
    cout << "Total number of times runway was idle " << a -> idle << endl;
    
    if (a -> landed > 0) // calculating the average waiting time when we have planes successfully landed
        cout << "The average wait time to land : " <<  (a -> LandWait / a -> landed) << endl;
    else // if no planes landed, it will print the number as it is without calculating (zero)
    cout << "The average wait time to land : " <<  a -> landed << endl;
    
    if (a -> tookoff > 0) // calculating the average waiting time when we have planes successfully tookoff
        cout << "The average wait time to takeoff : "  << (a -> TakeoffWait / a -> tookoff) << endl;
    else // if no planes tookoff, it will print the number as it is without calculating (zero)
        cout << "The average wait time to takeoff: " <<  a -> tookoff << endl;
    
    cout << "-------------------------------------------" <<endl;
}

int main(){
   
    mangeAirport a; // object of struct airport
    int curTime; // to keep track of the loop iterations, that will represent time
    int timetoland = 30; // time needed for planes to land (minutes)
    int timetotakeoff = 30; // time needed for planes to take off (minutes)
    plane temp; // object of struct plane
    
    display(); // to display the plane shape!
    
    initialAirport(&a); // initializing queue variables
    
    srand((unsigned)time(0));//function to genrate random numbers
    
    cout<<"\n- The program will run for 75 time units -" << endl << endl;
    
    
    for (curTime = 1; curTime <= 75; curTime++){// for loop from 1 to 75 (time units) to perform the simulation
      
      int fRandom = (rand() % 60)+1; //genrate random number between 1-60 for landing plane
      
        if(fRandom < timetoland){// random needs to less than the time needed to land in order for it to accepted
        
        newRecord(&a, curTime);// creates new plane for landing
                if (airportIsFull(&a, 1)) // to check whether there's enough space in the landing queue
                     a.numRefuse++; // true (it's full), the planes will be refused
                else
                    airportEnQueue(&a, 1); // false (not full), the planes will be added to the landing queue
        }
        
      int sRandom = (rand() % 60)+1; //genrate random number between 1-60 for taking off plane
      
        if (sRandom < timetotakeoff) { // random needs to less than the time needed to takeff in order for it to accepted
            
        newRecord(&a, curTime);//creates new plane for taking off
                if (airportIsFull(&a, 2)) // to check whether there's enough space in the takeoff queue
                   a.numRefuse++; // true (it's full), the planes will be refused
                else
                   airportEnQueue(&a, 2); // false (not full), the planes will be added to the takeoff queue
            }
            
                    
            if (!(airportIsEmpty(&a, 1))){// processeing landing planes first when there since they have priority
                temp = airportDeQueue(&a, 1); // store the plane that will pop in temp
                succLand( &a, temp, curTime ); // take action on the plane that was dequeued
            }
            else if (!(airportIsEmpty(&a, 2))){ // only when landing is empty, taking off planes will be processed
                temp = airportDeQueue(&a, 2); // store the plane that will pop in temp
                succTookoff( &a, temp, curTime ) ; // take action on the plane that was dequeued
            }
            else // both queues are empty
                a.idle ++;
                
        cout<<"\n\tInformation for: " << curTime << " proccess ....\t" << endl << endl;
        print(&a, fRandom, sRandom); // prints statistics each time unit
            
        }
     
    return 0;
}
