/*
--Node description: 
...what the node is doing (functionally)... 
When node is created a timer is activated that will print every second a number. 
The next number is always a the old number plus one 
further it does nothing more than being alive
*/ 

/*
--Software changes:
one line per change 
(1) created 31.3.2025: developer-Tilmann Koster reviewer(s)-Niek Ottens 
(2) changed 01.4.2025: xxx functionality added ... : developer-Tilmann Koster reviewer(s)-Niek Ottens 
...
*/


//-- tester: Sander Gieling


//--general includes 
#include <cstdlib>
#include "rclcpp/rclcpp.hpp"
#include <rclcpp/clock.hpp>
#include <rclcpp/time.hpp>

//--custom includes 
//...

//--using 
//...

class Template_Walltimer : public rclcpp::Node 
{
 public: 
    //-- constuctor: 
    Template_Walltimer() : Node("template_walltimer_node")   /*constructor = multiple inheritance*/ 
    {
        //--communication and timer objects: 
        timer_template_= this->create_wall_timer(std::chrono::milliseconds(1000),std::bind(&Template_Walltimer::timer_template_function,this));
        //--customs functions:
        //... 
        my_time = my_clock_.now();
		// RCLCPP_INFO(this->get_logger() ,"Current time: %d sec and %d nanosec", my_time.seconds(), my_time.nanoseconds());

    }
    
    //-- communication and timer functions 
	//... 
	

    /*function binded to timer_ ...executed by timer */ 
    void timer_template_function()          
    { 
    /* your code   */

        RCLCPP_INFO(this->get_logger() ,"The time is : %d", my_time); //example code  
    
    /* your code */ 
    }

    //--customs functions:

private:
    //--rclcpp varabiables:
    rclcpp::TimerBase::SharedPtr timer_template_;
    //--custom variables
    rclcpp::Clock my_clock_;
	rclcpp::Time my_time;
    
};


int main(int argc,char *argv[])
{

rclcpp::init(argc,argv);

auto node = std::make_shared<Template_Walltimer>();
rclcpp::spin(node);
rclcpp::shutdown();

return 0;
}
