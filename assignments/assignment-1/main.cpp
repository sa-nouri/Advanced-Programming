
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h> 
#include <algorithm> 
#define RED 0
#define GREEN 1
#define BLUE 2
#define ENCRYPT 0
#define DECRYPT 1
#define ILLEGAL -1
using namespace std;
typedef struct Pixel
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}Pixel;

typedef struct Square
{
	float variance;
	int begining_x;
	int begining_y;
	int color;//It can be 0=RED; 1=GREEN; 2=BLUE.
}Square;

void make_Squares_equal(Square& left_hand,const Square& right_hand)
{
	left_hand.variance=right_hand.variance;
	left_hand.begining_x=right_hand.begining_x;
	left_hand.begining_y=right_hand.begining_y;
	left_hand.color=right_hand.color;
}

int partition(vector <Square> &all_sqrz, int begin, int end)
{
	Square x ;
    make_Squares_equal(x ,all_sqrz[begin]);
    int i = begin - 1;
    int j = end + 1;
    Square temp;
    do
    {
        do      
        {
        	j--;
         }while (x.variance >all_sqrz[j].variance);
        do  
        {
        	i++;
        } while (x.variance <all_sqrz[i].variance);
         if (i < j)
         { 
			make_Squares_equal(temp , all_sqrz[i]);    
			make_Squares_equal(all_sqrz[i] ,all_sqrz[j]);
			make_Squares_equal(all_sqrz[j] , temp);
         }
    }while (i < j);     
    return j;
}
void quicksort(vector <Square> &all_sqrz, int begin, int end)
{      
     int middle;
     if (begin < end)
    {
          middle = partition(all_sqrz, begin, end);
          quicksort(all_sqrz, begin, middle);
          quicksort(all_sqrz, middle+1, end);
     }
     return;
}

vector<vector<Pixel> > ReadBMP(string file_name,unsigned char info_bytes[54])
{
	vector<vector<Pixel> > dump;
	ifstream img_file(file_name.c_str());
	if(!img_file)
	{
		cout<< "can't open file."<<endl;
		return dump;
	}
	unsigned char info[54];
	for(int c=0;c<54;c++)
	{
		info[c]=img_file.get();
		info_bytes[c]=info[c];
	}

    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    for(int j=0;j<height;j++)
    {
   		int row_padded=width*3;
    	if (row_padded%4!=0) row_padded+=4-((width*3)%4);
    	vector<Pixel> current_row;
    	vector<unsigned char> row_raw_data;
    	for(int k=0;k<row_padded;k++)
    		row_raw_data.push_back(img_file.get());
    	for(int i=0;i<3*width;i+=3)
    	{
    		Pixel to_add;
    		to_add.b=row_raw_data[i];
    		to_add.g=row_raw_data[i+1];
    		to_add.r=row_raw_data[i+2];
    		current_row.push_back(to_add);
    	}
    	dump.push_back(current_row);
    }
	return dump;
}

float calc_var(const vector<vector<Pixel> >& image,Square _sqr)
{
	int color=_sqr.color;
	int x_two=0;
	int sum=0;
	for(int j=0;j<8;j++)
	{
		for(int i=0;i<8;i++)
		{
			int sngl_pix_val;
			if(color==RED)
				sngl_pix_val=(int)image[j+_sqr.begining_y][i+_sqr.begining_x].r;
			else if(color==GREEN)
				sngl_pix_val=(int)image[j+_sqr.begining_y][i+_sqr.begining_x].g;
			else
				sngl_pix_val=(int)image[j+_sqr.begining_y][i+_sqr.begining_x].b;
			if(sngl_pix_val%2!=0) sngl_pix_val--;
			sum+=sngl_pix_val;
			x_two+=sngl_pix_val*sngl_pix_val;
		}
	}
	return ((float)x_two/64)-((float)sum/64)*((float)sum/64);
}

vector<Square> sqr_generator(const vector<vector<Pixel> >& image)
{
	vector<Square> sqrz;
	int height=image.size();
	int width=image[0].size();
	for(int j=0;j<height/8;j++)
	{
		int b_y=8*j;
		for(int i=0;i<width/8;i++)
		{
			int b_x=8*i;
			for(int k=0;k<3;k++)
			{
				Square to_add;
				to_add.begining_x=b_x;to_add.begining_y=b_y;
				to_add.color=k;
				to_add.variance=calc_var(image,to_add);
				sqrz.push_back(to_add);
			}
		}
	}
	return sqrz;
}
string get_secret_statement(int all_sqrz_size)
{
	string statement;
	cin.get();
	cout<<"Enter your secret statement."<<endl;
	std::getline(std::cin, statement);
	if (statement.size()*8+8 > all_sqrz_size)
	{
		cout<<"Too many charaters to embed in this image."<<endl;
		string zero_size;
		return zero_size;
	}
	return statement;
}

int read_seed()
{
	cout<<"Enter the seed."<<endl;
	int seed;
	cin>>seed;
	if(seed<1000 || seed>999999)
	{
		cout<<"Number is out of range."<<endl;
		return -1;
	}
	return seed;
}

int ith_bit(unsigned char statement_char,int i)//From left!!!
{
	unsigned char a=statement_char;
	for(int j=0;j<i;j++)
		a/=2;
	return a%2;
}
void make_lsb1(unsigned char& num)
{
	if(num%2!=1)
		num++;
}
void make_lsb0(unsigned char& num)
{
	if(num%2!=0)
		num--;
}
void embed_str2img(string statement,vector<vector<Pixel> >& image,const vector<Square>& all_sqrz)
{
	int sqr_index=0;
	statement.push_back('\n');
	for(int k=0;k<statement.size();k++)
	{
		unsigned char kth_char=statement[k];
		for(int i=0;i<8;i++)
		{
			int x=all_sqrz[sqr_index].begining_x+rand()%8;
			int y=all_sqrz[sqr_index].begining_y+rand()%8;
			if(all_sqrz[sqr_index].color==RED)
			{
				if(ith_bit(kth_char,i)==0) make_lsb0(image[y][x].r) ;
				if(ith_bit(kth_char,i)==1) make_lsb1(image[y][x].r) ;
			}
			if(all_sqrz[sqr_index].color==GREEN)
			{
				if(ith_bit(kth_char,i)==0) make_lsb0(image[y][x].g) ;
				if(ith_bit(kth_char,i)==1) make_lsb1(image[y][x].g) ;
			}
			if(all_sqrz[sqr_index].color==BLUE)
			{
				if(ith_bit(kth_char,i)==0) make_lsb0(image[y][x].b) ;
				if(ith_bit(kth_char,i)==1) make_lsb1(image[y][x].b) ;
			}
			sqr_index++;
		}
	}
}
bool save_img(string file_name,const vector<vector<Pixel> >& image,unsigned char info_bytes[54])
{
	int height=image.size();
    int width=image[0].size();
    ofstream img_out(file_name.c_str());
    if(!img_out)
    {
        cout<< "can't access memory."<<endl;
        return false;
    }
    for(int k=0;k<54;k++)
        img_out<<info_bytes[k];
    for(int j=0;j<height;j++)
    {
        int row_padded=width*3;
        if (row_padded%4!=0) row_padded+=4-((width*3)%4);
        for(int i=0;i<width;i++)
        {
            unsigned char num=0;
            img_out<<image[j][i].b;
            img_out<<image[j][i].g;
            img_out<<image[j][i].r;
            for(int dd=0;dd<row_padded-3*width;dd++)
                img_out<<num;
        }

    }
    return true;
}
int read_command()
{
	string command;
	cout<<"Please type your command."<<endl;
	cin>>command;
	if(command=="encrypt")
		return 0;
	else if(command=="decrypt")
		return 1;
	else
	{
		cout<<"Illegal request!"<<endl;
		return -1;
	}
}

bool encrypt()
{
	string file_name;
	unsigned char info_bytes[54];
	cout<<"Please enter file name."<<endl;
	cin>>file_name;
	vector<vector<Pixel> > image=ReadBMP(file_name,info_bytes);
	if(image.size()==0) return false;

	int seed=read_seed();
	if(seed==-1) return false;
	srand(seed);

	vector<Square> all_sqrz= sqr_generator(image);
	quicksort(all_sqrz,0,all_sqrz.size()-1);




	string statement=get_secret_statement(all_sqrz.size());
	if(statement.size()==0) return false;

	embed_str2img(statement,image,all_sqrz);
	save_img("output.bmp",image,info_bytes);
	return true;
}

string img2string(const vector<vector<Pixel> >& image,const vector<Square>& all_sqrz)
{
	string statement;
	unsigned char last_char=' ';
	while(last_char!='\n')
	{
		last_char=0;
		for(int k=0;k<8;k++)
		{
			int cur_sqr=8*statement.size()+k;
			int color=all_sqrz[cur_sqr].color;
			int x=all_sqrz[cur_sqr].begining_x+rand()%8;
			int y=all_sqrz[cur_sqr].begining_y+rand()%8;
			int secret_bit;
			if(color==RED)
				secret_bit=image[y][x].r%2;
			else if(color==GREEN)
				secret_bit=image[y][x].g%2;
			else//color==BLUE
				secret_bit=image[y][x].b%2;
			last_char+=(1<<k)*secret_bit;
		}
		statement.push_back(last_char);
	}
	return statement;
}


bool decrypt()
{
	string file_name;
	unsigned char info_bytes[54];
	cout<<"Please enter file name."<<endl;
	cin>>file_name;
	vector<vector<Pixel> > image=ReadBMP(file_name,info_bytes);
	if(image.size()==0) return false;

	int seed=read_seed();
	if(seed==-1) return false;
	srand(seed);

	vector<Square> all_sqrz= sqr_generator(image);
	quicksort(all_sqrz,0,all_sqrz.size()-1); 
	string secret_str=img2string(image,all_sqrz);
	cout<<secret_str;
	return true;
}

int main()
{

	int cmd=read_command();

	if(cmd==ENCRYPT)
	{
		if(!encrypt()) abort();
		else cout<<"Done."<<endl;
	}
	else if(cmd==DECRYPT)
	{
		if(!decrypt()) abort();
	}
	else 
	{//if(cmd==ILLEGAL)
		abort();
	}
}
