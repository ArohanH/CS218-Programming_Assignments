#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


class Point {
 public:
  double x;
  double y;

 public:
  Point()
      : x(0), y(0) {}  // Default constructor initializing coordinates to (0,0)
  Point(double xVal, double yVal)
      : x(xVal), y(yVal) {}  // Parameterized constructor

  double X() const { return x; }  // Accessor for x coordinate
  double Y() const { return y; }  // Accessor for y coordinate

};

double y_coordinate(pair<Point,Point> p, double x){
	if(p.second.X()-p.first.X()==0){
		return p.first.Y();
	}
	return p.first.Y()+(p.second.Y()-p.first.Y())*(x-p.first.X())/(p.second.X()-p.first.X());
}

bool is_intersecting(pair<Point,Point> p1, pair<Point,Point> p2){
	if((p1.second.Y()-p1.first.Y())/(p1.second.X()-p1.first.X())==(p2.second.Y()-p2.first.Y())/(p2.second.X()-p2.first.X())){
		return false;//parallel lines
	}
	else{
		//double x=((p2.second.Y()-p2.first.Y())*p2.first.X()*(p1.second.X()-p1.first.X())-(p1.second.Y()-p1.first.Y())*p1.first.X()*(p2.second.X()-p2.first.X()))/((p1.second.Y()-p1.first.Y())*(p2.second.X()-p2.first.X())-(p2.second.Y()-p2.first.Y())*(p1.second.X()-p1.first.X()));
		double x=((p1.first.Y()*(p1.second.X()-p1.first.X())-p1.first.X()*(p1.second.Y()-p1.first.Y()))*(p2.second.X()-p2.first.X())-(p2.first.Y()*(p2.second.X()-p2.first.X())-p2.first.X()*(p2.second.Y()-p2.first.Y()))*(p1.second.X()-p1.first.X()))/((p2.second.Y()-p2.first.Y())*(p1.second.X()-p1.first.X())-(p1.second.Y()-p1.first.Y())*(p2.second.X()-p2.first.X()));
		//cout << x << endl;
		if(p1.first.X()<=x && x<=p1.second.X()){
			if(p2.first.X()<=x && x<=p2.second.X()){
				return true;
			}
		}
	}

	return false;

}

Point interection_point(pair<Point,Point> p1, pair<Point,Point> p2){
	//double x=((p2.second.Y()-p2.first.Y())*p2.first.X()*(p1.second.X()-p1.first.X())-(p1.second.Y()-p1.first.Y())*p1.first.X()*(p2.second.X()-p2.first.X()))/((p1.second.Y()-p1.first.Y())*(p2.second.X()-p2.first.X())-(p2.second.Y()-p2.first.Y())*(p1.second.X()-p1.first.X()));
	double x=((p1.first.Y()*(p1.second.X()-p1.first.X())-p1.first.X()*(p1.second.Y()-p1.first.Y()))*(p2.second.X()-p2.first.X())-(p2.first.Y()*(p2.second.X()-p2.first.X())-p2.first.X()*(p2.second.Y()-p2.first.Y()))*(p1.second.X()-p1.first.X()))/((p2.second.Y()-p2.first.Y())*(p1.second.X()-p1.first.X())-(p1.second.Y()-p1.first.Y())*(p2.second.X()-p2.first.X()));
	double y=y_coordinate(p1,x);
	//cout << x << " " << y << endl;
	return Point(x,y);
}

// vector<pair<Point,Point>> divide_and_conquer(vector<pair<Point,Point>>& v){
// 	if(v.size()==1){
// 		//vector<Point> result;
// 		//result.push_back(v[0]);
// 		//result.push_back(v[0].first);
// 		//result.push_back(v[0].second);
// 		//result.push_back(Point(v[0].second.X(),0));
// 		return v;
// 	}
// 	vector <pair<Point, Point>> left;
// 	vector <pair<Point, Point>> right;
// 	int mid=v.size()/2;
// 	for(int i=0; i<mid; i++){
// 		left.push_back(v[i]);
// 	}
// 	for(int i=mid; i<v.size(); i++){
// 		right.push_back(v[i]);
// 	}
// 	vector <pair<Point,Point>> left_result=divide_and_conquer(left);
// 	vector <pair<Point,Point>> right_result=divide_and_conquer(right);
// 	return merge_for_me(left_result, right_result);
// }

vector<pair<Point,Point>> merge_for_me(vector<pair<Point,Point>>& left, vector<pair<Point,Point>>& right){
	//int last=left.size()-2;
	int i=0;
	int j=0;
	vector<pair<Point,Point>> result;
	while(i<left.size() && j<right.size()){
		if(left[i].second.X()<right[j].second.X()){//x2<x2'
			if(left[i].first.X()==right[j].first.X()){//x1=x1'
				if(is_intersecting(left[i],right[j])){//if lines interesect
					result.push_back(make_pair(Point(left[i].first.X(),max(left[i].first.Y(),right[j].first.Y())),interection_point(left[i],right[j])));
					result.push_back(make_pair(interection_point(left[i],right[j]),Point(left[i].second.X(),max(left[i].second.Y(),y_coordinate(right[j],left[i].second.X())))));
				}
				else{//if they don't interesect
					result.push_back(make_pair(Point(left[i].first.X(),max(left[i].first.Y(),right[j].first.Y())),Point(left[i].second.X(),max(left[i].second.Y(),y_coordinate(right[j],left[i].second.X())))));
				}
				right[j].first=Point(left[i].second.X(),y_coordinate(right[j],left[i].second.X()));
			}
			else if(left[i].first.X()<right[j].first.X()){
				if(left[i].second.X()<right[j].first.X()){
					result.push_back(left[i]);
					//result.push_back(right[j]);
				}
				else{
					if(is_intersecting(left[i],right[j])){//if lines intersect
						//cout << "It should not come here input 11\n";
						result.push_back(make_pair(left[i].first,Point(right[j].first.X(),y_coordinate(left[i],right[j].first.X()))));
						result.push_back(make_pair(Point(right[j].first.X(),max(right[j].first.Y(),y_coordinate(left[i],right[j].first.X()))),interection_point(left[i],right[j])));
						result.push_back(make_pair(interection_point(left[i],right[j]),Point(left[i].second.X(),max(left[i].second.Y(),y_coordinate(right[j],left[i].second.X())))));
					}
					else{
						result.push_back(make_pair(left[i].first,Point(right[j].first.X(),y_coordinate(left[i],right[j].first.X()))));
						result.push_back(make_pair(Point(right[j].first.X(),max(right[j].first.Y(),y_coordinate(left[i],right[j].first.X()))),Point(left[i].second.X(),max(left[i].second.Y(),y_coordinate(right[j],left[i].second.X())))));
					}
					right[j].first=Point(left[i].second.X(),y_coordinate(right[j],left[i].second.X()));

				}
			}
			else{
				if(is_intersecting(left[i],right[j])){
					result.push_back(make_pair(right[j].first,Point(left[i].first.X(),y_coordinate(right[j],left[i].first.X()))));
					result.push_back(make_pair(Point(left[i].first.X(),max(left[i].first.Y(),y_coordinate(right[j],left[i].first.X()))),interection_point(left[i],right[j])));
					result.push_back(make_pair(interection_point(left[i],right[j]),Point(left[i].second.X(),max(left[i].second.Y(),y_coordinate(right[j],left[i].second.X())))));
				}
				else{
					result.push_back(make_pair(right[j].first,Point(left[i].first.X(),y_coordinate(right[j],left[i].first.X()))));
					result.push_back(make_pair(Point(left[i].first.X(),max(left[i].first.Y(),y_coordinate(right[j],left[i].first.X()))),Point(left[i].second.X(),max(left[i].second.Y(),y_coordinate(right[j],left[i].second.X())))));
				}
				right[j].first=Point(left[i].second.X(),y_coordinate(right[j],left[i].second.X()));
			}
			//right[j].first=Point(left[i].second.X(),y_coordinate(right[j],left[i].second.X()));
			i++;
		}
		else if(left[i].second.X()==right[j].second.X()){
			if(left[i].first.X()==right[j].first.X()){
				if(is_intersecting(left[i],right[j])){
					result.push_back(make_pair(Point(left[i].first.X(),max(left[i].first.Y(),right[j].first.Y())),interection_point(left[i],right[j])));
					result.push_back(make_pair(interection_point(left[i],right[j]),Point(left[i].second.X(),max(left[i].second.Y(),right[j].second.Y()))));
				}
				else{
					result.push_back(make_pair(Point(left[i].first.X(),max(left[i].first.Y(),right[j].first.Y())),Point(left[i].second.X(),max(left[i].second.Y(),right[j].second.Y()))));
				}
			}
			else if(left[i].first.X()<right[j].first.X()){
				if(is_intersecting(left[i],right[j])){
					result.push_back(make_pair(left[i].first,Point(right[j].first.X(),y_coordinate(left[i],right[j].first.X()))));
					result.push_back(make_pair(Point(right[j].first.X(),max(right[j].first.Y(),y_coordinate(left[i],right[j].first.X()))),interection_point(left[i],right[j])));
					result.push_back(make_pair(interection_point(left[i],right[j]),Point(left[i].second.X(),max(left[i].second.Y(),right[j].second.Y()))));
				}
				else{
					result.push_back(make_pair(left[i].first,Point(right[j].first.X(),y_coordinate(left[i],right[j].first.X()))));
					result.push_back(make_pair(Point(right[j].first.X(),max(right[j].first.Y(),y_coordinate(left[i],right[j].first.X()))),Point(left[i].second.X(),max(left[i].second.Y(),right[j].second.Y()))));
				}
			}
			else{
				if(is_intersecting(left[i],right[j])){
					result.push_back(make_pair(right[j].first,Point(left[i].first.X(),y_coordinate(right[j],left[i].first.X()))));
					result.push_back(make_pair(Point(left[i].first.X(),max(left[i].first.Y(),y_coordinate(right[j],left[i].first.X()))),interection_point(left[i],right[j])));
					result.push_back(make_pair(interection_point(left[i],right[j]),Point(left[i].second.X(),max(left[i].second.Y(),right[j].second.Y()))));
				}
				else{
					result.push_back(make_pair(right[j].first,Point(left[i].first.X(),y_coordinate(right[j],left[i].first.X()))));
					result.push_back(make_pair(Point(left[i].first.X(),max(left[i].first.Y(),y_coordinate(right[j],left[i].first.X()))),Point(right[j].second.X(),max(right[j].second.Y(),left[i].second.Y()))));
				}
			}
			i++;
			j++;
		}
		else{
			if(left[i].first.X()==right[j].first.X()){
				if(is_intersecting(left[i],right[j])){
					result.push_back(make_pair(Point(left[i].first.X(),max(left[i].first.Y(),right[j].first.Y())),interection_point(left[i],right[j])));
					result.push_back(make_pair(interection_point(left[i],right[j]),Point(right[j].second.X(),max(right[j].second.Y(),y_coordinate(left[i],right[j].second.X())))));
				}
				else{
					result.push_back(make_pair(Point(left[i].first.X(),max(left[i].first.Y(),right[j].first.Y())),Point(right[j].second.X(),max(right[j].second.Y(),y_coordinate(left[i],right[j].second.X())))));
				}
				left[i].first=Point(right[j].second.X(),y_coordinate(left[i],right[j].second.X()));
			}
			else if(left[i].first.X()<right[j].first.X()){
				if(is_intersecting(left[i],right[j])){
					result.push_back(make_pair(left[i].first,Point(right[j].first.X(),y_coordinate(left[i],right[j].first.X()))));
					result.push_back(make_pair(Point(right[j].first.X(),max(right[j].first.Y(),y_coordinate(left[i],right[j].first.X()))),interection_point(left[i],right[j])));
					result.push_back(make_pair(interection_point(left[i],right[j]),Point(right[j].second.X(),max(right[j].second.Y(),y_coordinate(left[i],right[j].second.X())))));
				}
				else{
					result.push_back(make_pair(left[i].first,Point(right[j].first.X(),y_coordinate(left[i],right[j].first.X()))));
					result.push_back(make_pair(Point(right[j].first.X(),max(right[j].first.Y(),y_coordinate(left[i],right[j].first.X()))),Point(right[j].second.X(),max(right[j].second.Y(),y_coordinate(left[i],right[j].second.X())))));
				}
				left[i].first=Point(right[j].second.X(),y_coordinate(left[i],right[j].second.X()));
			}
			else{
				if(left[i].first.X()>right[j].second.X()){
					result.push_back(right[j]);
					//result.push_back(left[i]);
				}
				else{
					if(is_intersecting(left[i],right[j])){
						result.push_back(make_pair(right[j].first,Point(left[i].first.X(),y_coordinate(right[j],left[i].first.X()))));
						result.push_back(make_pair(Point(left[i].first.X(),max(left[i].first.Y(),y_coordinate(right[j],left[i].first.X()))),interection_point(left[i],right[j])));
						result.push_back(make_pair(interection_point(left[i],right[j]),Point(right[j].second.X(),max(right[j].second.Y(),y_coordinate(left[i],right[j].second.X())))));
					}
					else{
						result.push_back(make_pair(right[j].first,Point(left[i].first.X(),y_coordinate(right[j],left[i].first.X()))));
						result.push_back(make_pair(Point(left[i].first.X(),max(left[i].first.Y(),y_coordinate(right[j],left[i].first.X()))),Point(right[j].second.X(),max(right[j].second.Y(),y_coordinate(left[i],right[j].second.X())))));
					}
					left[i].first=Point(right[j].second.X(),y_coordinate(left[i],right[j].second.X()));
				}
				
			}
			//left[i].first=Point(right[j].second.X(),y_coordinate(left[i],right[j].second.X()));
			j++;
		}
	}
	while(j<right.size()){
		result.push_back(right[j]);
		j++;
	}
	while(i<left.size()){
		result.push_back(left[i]);
		i++;
	}
	return result;
}

vector<pair<Point,Point>> divide_and_conquer(vector<pair<Point,Point>>& v){
	if(v.size()==1){
		//vector<Point> result;
		//result.push_back(v[0]);
		//result.push_back(v[0].first);
		//result.push_back(v[0].second);
		//result.push_back(Point(v[0].second.X(),0));

		return v;
	}
	vector <pair<Point, Point>> left;
	vector <pair<Point, Point>> right;
	int mid=v.size()/2;
	for(int i=0; i<mid; i++){
		left.push_back(v[i]);
	}
	for(int i=mid; i<v.size(); i++){
		right.push_back(v[i]);
	}
	vector <pair<Point,Point>> left_result=divide_and_conquer(left);
	vector <pair<Point,Point>> right_result=divide_and_conquer(right);
	return merge_for_me(left_result, right_result);
}

int main(){
	   /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
	int n;
	cin >> n;
	double a,b,c,d;

	vector <pair<Point, Point> > posters; 

	for(int i=0; i<n; i++){
		cin >> a;
		cin >> b;
		cin >> c;
		cin >> d;

		if(a>c){
			double temp1=a;
			double temp2=b;
			a=c;
			b=d;
			c=temp1;
			d=temp2;
		}

		posters.push_back(make_pair(Point(a,b), Point(c,d)));	
	}

	//sort(std::begin(posters),std::end(posters));
	vector<pair<Point,Point>> result=divide_and_conquer(posters);

	double lengthCovered =0; 
	double area =0;

	for(int j=0;j<result.size();j++){
		lengthCovered=lengthCovered+result[j].second.X()-result[j].first.X();
	}

	for(int i=0;i<result.size();i++){
		area=area+(result[i].first.Y()+result[i].second.Y())*(result[i].second.X()-result[i].first.X())*0.5;
		//cout << result[i].first.X() << " " << result[i].first.Y() << endl; //" " << result[i].second.X() << " " << result[i].second.Y() << " \n"; 
	}
 
	std::cout << static_cast<int>(lengthCovered)<< endl;
	
	std::cout << static_cast<int>(area)<< endl;

	return 0;
}

