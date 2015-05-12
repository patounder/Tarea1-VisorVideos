#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <sstream>
#include <ctype.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>


std::vector<std::string> split(std::string string, const char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(string);
	std::string item;
	while (std::getline(ss, item, delim)) {
		if (!item.empty())
			elems.push_back(item);
	}
	return elems;
}

int main(int argc, char **argv) {
	
	if (argc != 3) {
		std::cout << "\n\nUso: " << argv[0] << " <<video_filename>> <<type_transformation>>\n"<< std::endl; 
		std::cout << "type_transformation = [ AJUSTE_a_b | CONV_a_b_c_d_e_f_g_h_i | MEDIANA_a (a Impar) ]\n"<< std::endl;
		std::cout << "Los valores a, b, c, d, e, f, g, h y i deben ser numeros\n\n]"<< std::endl;
		return 0;
	} else{
	
	cv::VideoCapture cap(argv[1]); // open the video file for reading

    if ( !cap.isOpened() )  // if not success, exit program
    {
         std::cout << "Cannot open the video file" << std::endl;
         return -1;
    }

    	
	std::string str_ajuste ("AJUSTE");
	std::string str_conv ("CONV");
	std::string str_med ("MEDIANA");
  	
	std::string trans_up(argv[2]);
	transform(trans_up.begin(), trans_up.end(), trans_up.begin(),(int (*)(int))toupper);//para que reconozca aunque este con minusculas
	
	std::string parameters=std::string(trans_up);
	std::vector<std::string> p = split(parameters, '_');
		
	
	if((str_ajuste.compare(p[0])) == 0){//Si es AJUSTE
	
	//create windows
    cv::namedWindow("Ajuste", CV_WINDOW_AUTOSIZE);
	
	for (;;){
        
		cv::Mat frame, gray;
		
        bool bSuccess = cap.read(frame); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
                 std::cout << "Cannot read the frame from video file" << std::endl;
                 break;
        }
		
		cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
		//gray = 255 - gray;
        gray = 255 - stof(p[1]) * gray + stof(p[2]);
				
		cv::imshow("Ajuste", gray);

       if (cv::waitKey(30) == 27)         {
                std::cout << "esc key is pressed by user" << std::endl; 
                break; 
        }
    }
    return 0;	

	}else{
		if((str_conv.compare(p[0])) == 0){//Si es CONV
			
		//create windows
		cv::namedWindow("Convolucion", CV_WINDOW_AUTOSIZE);
		
		for (;;){
		
		cv::Mat frame, gray;
		
		bool bSuccess = cap.read(frame); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
                 std::cout << "Cannot read the frame from video file" << std::endl;
                 break;
        }
		cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
		//gray = 255 - gray;
	
		//cv::Mat kernel = (cv::Mat_<float>(3,3) << a,b,c,d,e,f,g,h,i);
		cv::Mat kernel = (cv::Mat_<float>(3,3) << stof(p[1]),stof(p[2]),stof(p[3]),stof(p[4]),stof(p[5]),stof(p[6]),stof(p[7]),stof(p[8]),stof(p[9]));
	
		
		
		filter2D(gray,gray,-1,kernel,cv::Point(-1,-1),0,cv::BORDER_DEFAULT);
		cv::imshow("Convolucion", gray);

		if (cv::waitKey(30) == 27)         {
				std::cout << "esc key is pressed by user" << std::endl; 
				break; 
		}
		}
		
		return 0;	
		}else{
			if((str_med.compare(p[0])) == 0){//Si es Mediana
				
				
				//create windows
				cv::namedWindow("Mediana", CV_WINDOW_AUTOSIZE);
				
				for (;;){
			
				cv::Mat frame, gray;
				
				bool bSuccess = cap.read(frame); // read a new frame from video

				 if (!bSuccess) //if not success, break loop
				{
						 std::cout << "Cannot read the frame from video file" << std::endl;
						 break;
				}
				cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
				
				medianBlur(gray, gray,stoi(p[1]));				
				
				cv::imshow("Mediana", gray);

				if (cv::waitKey(30) == 27)         {
						std::cout << "esc key is pressed by user" << std::endl; 
						break; 
				}
				}
				
			return 0;
				
			}else{
			std::cout << "\n\nUso: " << argv[0] << " <<video_filename>> <<type_transformation>>\n"<< std::endl; 
			std::cout << "type_transformation = [ AJUSTE_a_b | CONV_a_b_c_d_e_f_g_h_i | MEDIANA_a (a impar)]\n"<< std::endl;
			std::cout << "Los valores a, b, c, d, e, f, g, h y i deben ser numeros\n\n]"<< std::endl;
				return 1;
			}
		}
	}
		
	/*for (;;) {
		if (!capture.grab() || !capture.retrieve(frame))
			break;
		
		//std::cout << "valor frame " << frame << std::endl;
		cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
		gray = 255 - gray;
		cv::imshow("VIDEO", gray);
		char c = cv::waitKey(33);
		if (c == 27)
			return 0;
	}*/
	cv::waitKey(0);
	return 0;
	}
}



