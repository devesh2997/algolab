#include<bits/stdc++.h>
#include<math.h>

 using namespace std;
 #define PI 3.14159265

 class DFT_Coefficient{
    public:
        double real, img;
        DFT_Coefficient(){
            real = 0.0;
            img = 0.0;
        }
};

int main(){
    int N = 10;    
    cout << "Enter coefficients of the simple linear function:\n";    
    double a, b, c;
    cin >> a >> b >> c; 
    double function[N];
    for (int i = 0; i < N; i++){
        function[i] = (((a * (double) i) + (b * (double) i)) - c);
    } 
    cout << "Enter the max K value: ";
    int k;
    cin >> k; 
    double cosine[N]; double sine[N]; 
    for (int i = 0; i < N; i++){
        cosine[i] = cos((2 * i * k * PI) / N);
        sine[i] = sin((2 * i * k * PI) / N);
    }
 
    DFT_Coefficient dft_val;
    cout << "The coefficients are: ";
 
    for (int i = 0; i < N; i++){
        dft_val.real += function[i] * cosine[i];
        dft_val.img += function[i] * sine[i];
    }
    cout << "(" << dft_val.real << ") - " << "(" << dft_val.img << " i)"; 
}
