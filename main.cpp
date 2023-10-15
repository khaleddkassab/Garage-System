
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;
class SetSize
{
public:
    int Size=20;
     void SettSize(int size)
    {
        Size=size;
    }
};

class TotalIncome
{
    static TotalIncome *instance;
   // Private constructor so that no objects can be created.
   TotalIncome(){}

   public:
   static TotalIncome* getInstance()
   {
      if ( instance == NULL)
      {
      instance = new TotalIncome();
      }
      return  instance;
   }

    public:
        int TotalIncomee=0;
};
TotalIncome * TotalIncome::instance=NULL;

class Display//iNTERFACE abstract class
{
public:
    virtual void Displayy()=0;
};


class Release//iNTERFACE abstract class
{
public:
    virtual void Reset ()=0;
};

class Time :public Release
{
public:
    int ArrivalHours;
    int ArrivalMinutes;
    int ArrivalSeconds;
    int DepartureHours;
    int DepartureMinutes;
    int DepartureSeconds;
    Time ()
    {
        Reset();
    }


    void ArrivalTime ()
    {
        time_t now =time(0);
                tm *ltm=localtime(&now);
                ArrivalHours  =ltm->tm_hour;
                ArrivalMinutes=ltm->tm_min;
                ArrivalSeconds=ltm->tm_sec;
                cout <<""<<endl;
                cout << "The time of Arrival is: " <<ArrivalHours<<":" <<ArrivalMinutes <<":"<<ArrivalSeconds<<endl;

    }
    void DisplayArrivalTime ()
    {
        cout << "The local date and time of Arrival is: " <<ArrivalHours<<":"<<ArrivalMinutes <<":"<<ArrivalSeconds<< endl;
    }
    void DepartureTime ()
    {
       time_t now =time(0);
                tm *ltm=localtime(&now);
                DepartureHours  =ltm->tm_hour;
                DepartureMinutes=ltm->tm_min;
                DepartureSeconds=ltm->tm_sec;
    }
    void DisplayDepartureTime ()
    {
        cout << "The local date and time of Departure is: " << DepartureHours<<':'<<DepartureMinutes<<':'<<DepartureSeconds << endl;
    }
    void Reset ()
    {
        ArrivalHours     =0 ;
        ArrivalMinutes   =0 ;
        ArrivalSeconds   =0 ;
        DepartureHours   =0 ;
        DepartureMinutes =0 ;
        DepartureSeconds =0 ;

    }

};
class Dimensions
{
public:
    float Depth;
    float Width;

    bool CompareDimensions(Dimensions D)
    {
        if (Depth >=D.Depth && Width>=D.Width )
        {
            return true;
        }
        else
            return false;
    }
};


class Vehicle:public Release,public Display
{

public:
    string Name;
    string ID;
    int ModelYear;
    string MobileNumber;
    string Email;
    Dimensions OfVehicle;

    /*Vehicle (Vehicle Argu)
    {
        Name           =Argu.Name ;
        ID             =Argu.ID ;
        ModelYear      =Argu.ModelYear;
        OfVehicle.Depth=Argu.OfVehicle.Depth;
        OfVehicle.Width=Argu.OfVehicle.Width;

    }*/
    Vehicle () //default constructor
    {
       Reset();
    }

    void Reset()//to clear the vehicle info after going out the garage
    {
        Name                 ="";
        ID                   ="";
        MobileNumber         ="";
        Email                ="";
        ModelYear            =0 ;
        OfVehicle.Depth      =0 ;
        OfVehicle.Width      =0 ;


    }
    void Displayy ()
    {
        cout<<"Vehicle Name                   : "<<Name     <<endl;
        cout<<"Vehicle Unique ID              : "<<ID       <<endl;
        cout<<"Vehicle Model Year             : "<<ModelYear<<endl;
        cout<<"Vehicle Owner Mobile Number    : "<<MobileNumber<<endl;
        cout<<"Vehicle Owner E-mail           : "<<Email<<endl;
        cout<<"Vehicle Dimensions             : "<<OfVehicle.Depth<<" * "<<OfVehicle.Width<<endl;
    }
};

class Slot :public Display, public Release
{
public:
    int Status;
    Dimensions D;
    SetSize s;



    Slot(Dimensions s)//Parametrized constructor
    {
            D.Depth=s.Depth;
            D.Width=s.Width;
            Status=0;
    }

    Slot()//Default constructor
    {
           Reset();
    }
    void Reset ()
    {
        Status =0;
            D.Depth=0;
            D.Width=0;
    }
    void Displayy()
    {
        cout<<"Slot Dimensions                :"<<D.Width<<"*"<<D.Depth<<endl;
    }

    bool IsEmpty ()//to know if it is empty slot or no
    {
        if (Status==0)
            return true;
        else
            return false;
    }

};

class MaxSlot//to save max Dimensions
{
public:
    Dimensions MaxSpace;
    MaxSlot ()//just initiallization
    {
        MaxSpace.Depth=24;
        MaxSpace.Width=24;
    }

    void SetMaxSpace(MaxSlot M)//Set Max dimensions by comparing width and depth by the max width and depth
    {
        SetMaxDepth(M.MaxSpace);
        SetMaxWidth(M.MaxSpace);
    }
    void SetMaxDepth(Dimensions New )
    {
        if (New.Depth>= MaxSpace.Depth)
            MaxSpace.Depth=New.Depth;
    }
    void SetMaxWidth(Dimensions New )
    {
        if (New.Width>= MaxSpace.Width)
            MaxSpace.Width=New.Width;
    }


};

class GarageAppController//Application controller
{
   static GarageAppController *instance;
   // Private constructor so that no objects can be created.
   GarageAppController(){}

   public:
   static GarageAppController* getInstance()
   {
      if ( instance == NULL)
      {
      instance = new GarageAppController();
      }
      return  instance;
   }
        MaxSlot M;
        SetSize SizeOfGarage;
        TotalIncome * TotalIncome = TotalIncome::getInstance();
        Dimensions VehicleDimensions;

        Slot    *slot           =   new Slot   [SizeOfGarage.Size];
        Time    *arrOfTime      =   new Time   [SizeOfGarage.Size];
        Vehicle *arrOfVehicles  =   new Vehicle[SizeOfGarage.Size];

};
//Static member to make only one object creation of the controller
GarageAppController * GarageAppController::instance=NULL;

//Display all arrays
class DisplayAllVehicleInfo
{
public:
    void Display(GarageAppController * g,int Slot)
    {
        cout<<"Slot Number                    : "<<Slot+1<<endl;
        g->arrOfVehicles[Slot].Displayy();
        g->slot         [Slot].Displayy();
        g->arrOfTime    [Slot].DisplayArrivalTime();

    }
    void DisplaySMS(GarageAppController * g,int Slot,int Fees)
    {
        cout<<"-------SMS-------"<<endl;
        Display(g,Slot);
        g->arrOfTime    [Slot].DisplayDepartureTime();
        cout<<"                 --------------------------------------"<<endl;
        cout<<"                     You have to pay : "<<Fees<<" L.E"<<endl;
    }
    void DisplayEMail(GarageAppController * g,int Slot,int Fees)
    {
        cout<<"-------E-mail-------"<<endl;
        Display(g,Slot);
        g->arrOfTime    [Slot].DisplayDepartureTime();
        cout<<"                 --------------------------------------"<<endl;
        cout<<"                     You have to pay : "<<Fees<<" L.E"<<endl;
    }
    void DisplayAllVehicles(GarageAppController * g)
    {
         for(int i=0; i<g->SizeOfGarage.Size; i++)
            {
                Display(g,i);

            }
    }
};

class SlotConfiguration
{
public:
    SetSize s;

    //to set slot dimensions as default
    SlotConfiguration(Slot slot[])
    {
        for(int x=5, i=0; i<s.Size; i++,x++)
        {
            slot[i].D.Depth=x;
            slot[i].D.Width=x;
        }
    }
    //to set maxSize of dimensions of slots
    bool SetMaxSize (GarageAppController *G,Dimensions New )
    {
        G->M.SetMaxDepth(New);
        G->M.SetMaxWidth(New);

    }
    //to change slot default dimensions
    int SetSlotSize(GarageAppController *G,Dimensions New,int index)
    {
        G->slot[index].D=New;
        cout<<G->slot[index].D.Depth<<G->slot[index].D.Width<<"from inside"<<endl;
        SetMaxSize(G,New);

    }
};
class SlotFunctions
{
public:
    SetSize s;
    //Display all empty slot
    void DisplayEmptySlots(Slot slot[])
    {
        cout<<"Empty Slots are :";
        for(int i=0; i<s.Size ; i++)
        {
            if (slot[i].Status==0)
                if (i==s.Size-1)
                    cout<<i+1;
                else
                cout<<i+1<<"-";

        }
        cout<<endl;
    }
    //Display all empty slots for specific dimension
    void DisplayEmptySlots(Slot slot[],Dimensions d)
    {
        cout<<"Empty Slots are :";
        for(int i=0; i<s.Size ; i++)
        {
            if (slot[i].Status==0 && slot[i].D.CompareDimensions(d))
                if (i==s.Size-1)
                    cout<<i+1;
                else
                cout<<i+1<<"-";

        }
        cout<<endl;
    }
    bool IsEmpty (Slot slot[],int index)
    {
        if (slot[index].Status==0)
        {
            return true;
        }
        else
            return false;
    }

};

class SlotAlgorithms//iNTERFACE abstract class
{
public:
    SetSize s;

    virtual int SlottAlgorithm (GarageAppController * G){}

};
class FirstFitAlgorithm :public SlotAlgorithms
{
public:
     int SlottAlgorithm (GarageAppController * G)
    {
         for (int i=0; i<G->SizeOfGarage.Size; i++)
        {
            if  (G->slot[i].D.CompareDimensions(G->VehicleDimensions) && G->slot[i].IsEmpty())
            {
                return i;
            }
        }
    }
};

class BestFitAlgorithm :public SlotAlgorithms
{
public:
    int SlottAlgorithm (GarageAppController * G)//return to the vehicle the first empty slot
    {
        int BestFit=0;
        for (int i=0; i<G->SizeOfGarage.Size; i++)
        {
            if (G->slot[i].D.CompareDimensions(G->VehicleDimensions) && G->slot[i].IsEmpty() )
            {
                BestFit=i;
                break;

            }
        }
        for (int i=BestFit+1;i<G->SizeOfGarage.Size;i++)
        {
            if ( G->slot[BestFit].D.CompareDimensions(G->slot[i].D) && G->slot[i].D.CompareDimensions(G->VehicleDimensions) && G->slot[i].IsEmpty() )
                {
                    BestFit=i;
                }
        }
        return BestFit;
    }

};
class ParkIn
{

public:
    int SlotInt=0,ModelYear;
    SetSize s;
    Vehicle V;
    string modYear;


    int RequestToPark(GarageAppController *G,int alg)//all empty slots =0 if all =1 therefore no empty slots
    {
        for (int i=0; i<G->SizeOfGarage.Size; i++)
        {
            if (G->slot[i].D.CompareDimensions(G->VehicleDimensions) && G->slot[i].Status==0)
            {
                    if (alg==1)
                    {
                        SlotAlgorithms * Algorithm = new FirstFitAlgorithm;
                        SlotInt=Algorithm->SlottAlgorithm(G);
                    }
                    if (alg==2)
                    {

                        SlotAlgorithms * Algorithm = new BestFitAlgorithm;
                        SlotInt = Algorithm->SlottAlgorithm(G);
                    }
                    cout <<""<<endl;
                    cout<<"Vehicle Name      : ";
                    cin>>V.Name;
                    cout<<"Vehicle Unique ID : ";
                    cin>>V.ID;
                    cout<<"Vehicle Model Year: ";
                    V.OfVehicle.Depth=G->VehicleDimensions.Depth;
                    V.OfVehicle.Width=G->VehicleDimensions.Width;

                    try
                    {
                        cin>>modYear;

                        if (ModelYear=stoi(modYear) )//to enter a valid model year
                        {
                            if (ModelYear>=1975 )
                            {
                                V.ModelYear=ModelYear;
                            }

                            else
                            {
                                throw ModelYear;
                            }

                        }
                        else
                            throw ModelYear;
                    }
                    catch( int a )
                    {
                        cout<<ModelYear<< " is not a Valid Model year  !!"<<endl;
                        V.Reset();
                        cout <<""<<endl;
                        continue;
                    }
                    catch( exception &err)
                    {
                        cout<<"Please Enter Correct Model Year  !!"<<endl;
                        V.Reset();
                        cout <<""<<endl;
                        continue;
                    }
                    cout<<"Mobile Number     : ";
                    cin>>V.MobileNumber;
                    cout<<"E-mail Address    : ";
                    cin>>V.Email;

                    cout<<"You can Park your Vehicle in Slot number : "<<SlotInt+1<<endl;
                    G->slot[SlotInt].Status=1;

                    //function to calculate  Arrival time
                    G->arrOfTime[SlotInt].ArrivalTime();

                    //save vehicle info in an arr of vehicles
                    G->arrOfVehicles[SlotInt]=V;

                    return SlotInt;

                }

        }
        return -1;

    }
};

class CalculateFees
{

public:
    int fees=0;
    int HourPrice;
    //
    virtual void SetHourPrice (int x)=0;
    virtual int CalculateFee (Time Time,Slot s)=0;

};
class CalFees:public CalculateFees
{

public:

void SetHourPrice (int x)
    {
        HourPrice=x;
    }


int CalculateFee (Time Time,Slot s)
{
    //calculate Total Hours
    int totalHours=Time.DepartureHours-Time.ArrivalHours ;
    int totalMins =Time.DepartureMinutes-Time.ArrivalMinutes;

    //price according to slot dimensions
        if (s.D.Depth<=10 || s.D.Width<=10)
        {
            HourPrice=5;
        }
        if (  (s.D.Depth<=15 &&s.D.Depth>10) || (s.D.Width<=15 &&s.D.Width>10) )
        {
            HourPrice=10;
        }
        if (  (s.D.Depth<=20 &&s.D.Depth>15) || (s.D.Width<=20 &&s.D.Width>15) )
        {
            HourPrice=15;
        }
        else
        {
            HourPrice=20;
        }

    //to make if he broke the hour pay the whole hour
    if (totalMins<0 || (totalMins==0&& totalHours>0))
    {
        fees=totalHours*HourPrice;
        return fees;
    }
    else if (totalMins>0&& totalHours>0)
    {
        totalHours++;
        fees=totalHours*HourPrice;
        return fees;
    }
    else
    {
        totalHours=1;
        fees=totalHours*HourPrice;
        return fees;
    }
 }
};

class ParkOut
{

public:

    //to free the slot after the vehicle leave the garage
    void Release (GarageAppController * G,int index)
    {
        G->slot         [index].Status  =0;
        G->arrOfVehicles[index].Reset   ();
        G->arrOfTime    [index].Reset   ();
    }

    int RequestToLeave (GarageAppController * G,int index)
    {
        CalFees fees;
        int Fees;
        G->arrOfTime    [index].DepartureTime();

        DisplayAllVehicleInfo D;
        D.Display(G,index);
        G->arrOfTime[index].DisplayDepartureTime();


        //calculate fees
        Fees=fees.CalculateFee(G->arrOfTime[index],G->slot[index]);
        //free space


        cout <<"--------------------------------------"<<endl;
        cout<<" You have to pay : "<<Fees<<" L.E"<<endl;
        D.DisplayEMail(G,index,Fees);
        D.DisplaySMS(G,index,Fees);
        Release(G, index);
        //to save it in total income;
        G->TotalIncome->TotalIncomee+=Fees;
        return Fees;
    }
};

class CheckDimensions
{

public:
    float Depth,Width;
    string Len,Wid;
    Dimensions VehicleDimensions;


    int Check(GarageAppController * G)
    {
        cout<<"Please Enter Car Length :";

                    try
                    {
                        cin>>Len;

                        if (VehicleDimensions.Depth=stof(Len) )//to enter a valid length
                        {
                            if (VehicleDimensions.Depth<=G->M.MaxSpace.Depth ){Depth=VehicleDimensions.Depth;}

                            else
                            {throw VehicleDimensions.Depth;}

                        }
                        else
                            throw VehicleDimensions.Depth;
                    }
                    catch( float a)
                    {
                        cout<< " We have not the required Dimensions  !!"<<endl;
                        cout <<""<<endl;
                        return -1;
                    }
                    catch( exception &err)
                    {
                        cout<<"Please Enter Correct Length  !!"<<endl;
                        cout <<""<<endl;
                        return -1;
                    }

            cout<<"Please Enter Car Width :";
            try
                    {
                        cin>>Wid;

                        if (VehicleDimensions.Width=stof(Wid) )//to enter a valid Width
                        {
                            if (VehicleDimensions.Width<=G->M.MaxSpace.Width){Width=VehicleDimensions.Width;}

                            else
                            {throw VehicleDimensions.Width;}

                        }
                        else
                            throw VehicleDimensions.Width;
                    }
                    catch( float a)
                    {
                        cout<< " We have not the required Dimensions  !!"<<endl;
                        cout <<""<<endl;
                        return -1;

                    }
                    catch( exception &err)
                    {
                        cout<<"Please Enter Correct Width  !!"<<endl;
                        cout <<""<<endl;
                        return -1;

                    }
                    /*if (VehicleDimensions.Depth==slot[SizeOfGarage.Size-1].D.Depth &&slot[SizeOfGarage.Size-1].Status!=0)
                    {
                        cout<<"The required Dimensions is not available "<<endl;

                    }*/
    }

} ;


class Screen
{
public:
    Screen()
    {
        cout <<" Welcome to Garage Application : " << endl;
    cout <<"---------------------------------"<<endl;
    cout <<""<<endl;


    ParkIn  P;
    ParkOut L;
    Vehicle V;
    SlotFunctions A;
    CheckDimensions C;
    GarageAppController * Garage = GarageAppController::getInstance();

    SlotConfiguration Config(Garage->slot);

    string Name,ID,modYear,ArrHours;
    int Button=1,i=0,NumOfVehicles=0,ModelYear,VehicleSlot,SortingType=2;



    while (Button==1 || Button==2 ||Button==3 || Button==4 || Button==5|| Button==6 || Button==7 ||Button==8)
    {
        cout <<""<<endl;

        cout<<"Press Button 1 to Park"                        <<endl;
        cout<<"Press Button 2 to Request To leave "           <<endl;
        cout<<"Press Button 3 to Display Empty Slots "        <<endl;
        cout<<"Press Button 4 to Display Total Income "       <<endl;
        cout<<"Press Button 5 to Display all Vehicles "       <<endl;
        cout<<"Press Button 6 to Display Required Vehicle    "<<endl;
        cout<<"Press Button 7 to Display Application settings"<<endl;
        cout<<"Press Button 8 to Display Fit Slots  "         <<endl;
        cin>>Button;

        if (Button==1)
        {
                if (C.Check(Garage)==-1)
                {
                  continue;

                }
                    //assign to vd. the user input
                    Garage->VehicleDimensions.Depth=C.Depth;
                    Garage->VehicleDimensions.Width=C.Width;

                if (P.RequestToPark(Garage,SortingType)!=-1)//if there is a viable slot
                {
                    //to know number of cars used the garage
                    NumOfVehicles++;

                    //condition to not let him enter vehslot and there is no parked slots
                    i++;

                }
        }
            if (Button==2 && i>0)////to not let user request leave and there is no vehicles
            {
                int VehSlot;

                cout<<"Which Slot your Vehicle is  : "<<endl;
                cin>>VehSlot;

                //function to check if the garage is empty and to to not enter vehslot greater than size of garage
                if (!A.IsEmpty(Garage->slot,VehSlot-1) && VehSlot<Garage->SizeOfGarage.Size+1)
                {
                    //function for leaving
                    L.RequestToLeave(Garage,VehSlot-1);

                    //to decrement if vehicle has gone
                    i--;

                }
                else //to not let user request leave to a slot has no vehicle
                {
                    cout<<"This is an Empty Slot !!"<<endl;
                    continue;
                }

                if (VehSlot>Garage->SizeOfGarage.Size)
                {
                    cout<<"This is not a Slot in the Garage !!"<<endl;
                }


            }
            if (Button==3)
            {
                A.DisplayEmptySlots(Garage->slot);
            }

            if (Button==4)
            {
                //to make authorization
                string UserName="Admin",Password="Admin",UName,Pass;
                cout<<"User Name : ";
                cin>>UName;
                cout<<"Password :";
                cin>>Pass;
                if (UserName==UName && Password==Pass)
                {
                    cout<<"Total income is             : "<<Garage->TotalIncome->TotalIncomee<<endl;
                    cout<<"Total number of vehicles is : "<<NumOfVehicles<<endl;
                }
                else
                {
                    cout<<"Your are not authorized !!"<<endl;
                }

            }

        if (Button==5)
        {
            DisplayAllVehicleInfo D;
            D.DisplayAllVehicles(Garage);
        }
        if (Button==6)
        {
            int VehicleSlot;
            DisplayAllVehicleInfo D;

                cout<<"Which Vehicle you want to display : "<<endl;
                cin>>VehicleSlot;
                D.Display(Garage,VehicleSlot-1);


        }
        if (Button==7)
        {
            int key=1,index;
            Dimensions NewD;
            CheckDimensions D;


            while (key>0 && key <=2)
            {
                cout<<"Press Button 1 to change Slot Dimensions : "        <<endl;
                cout<<"Press Button 2 to change Slot Choosing Algorithm : "<<endl;
                cin>>key;
                if (key==1)
                {

                    cout<<"Enter Required to Change Slot : ";
                    cin>>index;
                    if (index<Garage->SizeOfGarage.Size &&index>=0)
                    {
                        cout<<"Enter New Depth : ";
                        cin>>NewD.Depth;
                        cout<<"Enter New Width : ";
                        cin>>NewD.Width;

                        Config.SetSlotSize(Garage,NewD,index);
                        cout<<Garage->M.MaxSpace.Depth<<Garage->M.MaxSpace.Depth<<endl;

                        cout<<"Done successfully "<<endl;
                        break;
                    }
                    cout<<"invalid index!!"<<endl;
                    continue;

                }
                if (key==2)
                {
                    cout<<"Press Button 1 to First Fit Sorting Algorithm"<<endl;
                    cout<<"Press Button 2 to Best  Fit Sorting Algorithm"<<endl;
                    cin>>SortingType;
                    cout<<"Done successfully "<<endl;
                    break;

                }
            }

            /*int newsize;
            cout<<"Change Size Enter new Size :";
            cin>> newsize;
            SizeOfGarage.SettSize(newsize);*/
        }
        if (Button==8)
        {
            Dimensions d;
            if (C.Check(Garage)==-1)
                {continue;}
            //assign to vd. the user input
            d.Depth=C.Depth;
            d.Width=C.Width;

            A.DisplayEmptySlots(Garage->slot,d);
        }

    }

    }
};


int main()
{
    Screen s;
    return 0;
}
