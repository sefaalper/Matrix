#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
template <class T>
class Matrix
{
    public:
        Matrix();
        //~Matrix();
        Matrix(int a,int b,char c);
        Matrix(int, int, T);
        void resize(int row,int column);
        void print();
        void print(string a);
        Matrix<T> operator-(int);
        Matrix<T> operator+(int);
        Matrix<T> operator/(int);
        Matrix<T> operator*(int);
        Matrix<T> operator%(int);
        Matrix<T> operator^(int);
        Matrix<T> operator+(const Matrix<T>&);
        Matrix<T> operator*(const Matrix<T>&);
        Matrix<T> operator-(const Matrix<T>&);
        void operator=(const Matrix<T>&);
        Matrix<T> transpoze();
        Matrix<T> emul(const Matrix<T>&);
        double determinant();
        Matrix<double> inv();
        Matrix<T> cofactor(int,int);
        void setItem(int,int,T);

    protected:
        T **dizi;
        int satir;
        int sutun;
};

template <class T>
void Matrix<T>::setItem(int row,int column, T value)
{
	dizi[row][column] = value;
}
//parametre içermeyen constructor. 10x10 "0" değerli matris oluşturuyor
template <class T>
Matrix<T>::Matrix()
{
	satir=10;
	sutun=10;
    dizi= new T *[satir];
    for(int j=0;j<sutun;j++){
        dizi[j] = new T [sutun];
    }
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			dizi[i][j] = 0;
		}
	}
}
//parametre içeren constructor. Değer parametresi int!
template <class T>
Matrix<T>::Matrix(int g,int h,T f)
{
		satir = g;
		sutun = h;
		dizi = 0;
		dizi = new T*[satir];
		for (int i = 0; i < satir; i++)
		{
			dizi[i] = new T [sutun];
			for (int j = 0; j < sutun; j++)
			{
				dizi[i][j] = f;
			}
		}
}
// parametre içeren constructor. Parametresi char!
template <class T>
Matrix<T>::Matrix(int a,int b,char f)
{
	// random int değerler içeren matris oluşturuyor.
	if(f == 'r')
	{
		satir = a;
		sutun = b;
		dizi= new T *[satir];
    	for(int j=0;j<satir;j++){
        	dizi[j] = new T [sutun];
    	}
    	srand(time(NULL));
		for (int i = 0; i < satir; i++)
		{
			for (int j = 0; j < sutun; j++)
			{
				dizi[i][j] = rand()%(256);		
			}

		}
	}
	//birim matris oluşturuyor.
	else if(f == 'e')
	{
		//birim matrisin köşegenlerde 1 olması şartını içeriyor.
		if(a == b) 
		{
			satir = a;
			sutun = b;
			dizi= new T *[satir];
    		for(int j=0;j<satir;j++)
    		{
        		dizi[j] = new T [sutun];
    		}
			for (int i = 0; i < satir; i++)
	    	{
				for (int j = 0; j < sutun; j++)
				{
					if(i==j) dizi[i][j] = 1;
					else dizi[i][j] = 0;
				}

			}
		}
		else throw invalid_argument("Matris boyutları aynı olmalıdır");
}
		else if(f == 'L')
		{

			satir = a;
			sutun = b;
			double aa = 1.;
			dizi= new T *[satir];
    		for(int j=0;j<satir;j++)
    		{
        		dizi[j] = new T [sutun];
    		}
			for (int i = a; i > 0; i--)
	    	{
				for (int j = b; j > 0; j--)
				{
					if(a == b) dizi[i][j] = 1;
					else dizi[i][j] = 0;
				}

			}
		}
}
		//birim matriste satir ve sutun sayıları aynı olmalıdır.
template <class T>
void Matrix<T>::resize(int row,int column)
{
	// matris küçülecekse fazlalık kısımlarını siliyoruz.
   if(satir>row)
   {
   		for (int i=row;i<satir;i++)
   		{	
   			delete [] dizi[i];
   		}
   }
   //matris büyüyecekse uygun yer ayırma işi yapılıyor.
   else
   {	
   	   	dizi = (T**) realloc (dizi, row * sizeof(T*));
   }
   satir = row;
   for(int i = 0;i<satir;i++)
   	{
  	   	dizi[i] = (T*) realloc (dizi[i], column * sizeof(T));
   	}
   	sutun = column;
}
//matrisi ekrana yazdırıyor.
template <class T>
void Matrix<T>::print()
{
	cout << "Your matrix is: " << endl;
	for (int i = 0; i < satir; i++)
	{
		for (int j = 0; j < sutun; j++)
		{
			cout << setw(4)<<dizi[i][j];
		}
		cout<<'\n'<<endl;
	}
}
//matrisi dosyaya yazdırıyor. Parametre olarak string alıyor.
template <class T>
void Matrix<T>::print(string a)
{
	ofstream dosya;
	dosya.open("file.txt");
	dosya<< "Your matrix is: " << endl;

	for (int i = 0; i < satir; i++)
	{
		for (int j = 0; j < sutun; j++)
		{
			dosya << dizi[i][j]<<"  ";
		}
		dosya<<'\n'<<endl;
	}
	dosya.close();
}
//Matrisin transpozesini alıyor. 
//Transpoze işlemi için nesne kullanıldı
template <class T>
Matrix<T> Matrix<T>::transpoze()
{
	Matrix<T> temp(sutun,satir,(T)0);
	for(int i=0;i<satir;i++)
	{
		for(int j = 0;j<sutun;j++) 
			{
				temp.dizi[j][i] = dizi[i][j];
			}
	}
	return temp;
}
// "+" operatörü için overload
template <class T>
Matrix<T> Matrix<T>::operator+(int t)
{
	Matrix<T> m(this->satir,this->sutun,(T)0);
	for(int i = 0; i < this->satir;i++)
		for(int j = 0;j < this->sutun;j++)
			m.dizi[i][j] = this->dizi[i][j] + t;
		return m;
}
//"-" operatörü için overload
template <class T>
Matrix<T> Matrix<T>::operator-(int s)
{
	Matrix<T> m(this->satir,this->sutun,(T)0);
	for(int i = 0; i < this->satir;i++)
		for(int j = 0;j < this->sutun;j++)
			m.dizi[i][j] = this->dizi[i][j] - s;
		return m;
}
// "/" operatörü için overload
template <class T>
Matrix<T> Matrix<T>::operator/(int k)
{
	Matrix<T> m(this->satir,this->sutun,(T)0);
	for(int i = 0; i < this->satir;i++)
		for(int j = 0;j < this->sutun;j++)
			m.dizi[i][j] = this->dizi[i][j] / k;
		return m;
}
//"*" operatörü için overload
template <class T>
Matrix<T> Matrix<T>::operator*(int b)
{
	Matrix<T> m(this->satir,this->sutun,(T)0);
	for(int i = 0; i < this->satir;i++)
		for(int j = 0;j < this->sutun;j++)
			m.dizi[i][j] = this->dizi[i][j] * b;
		return m;
}
// "%" operatörü için overload
template <class T>
Matrix<T> Matrix<T>::operator%(int y)
{
	Matrix<T> m(this->satir,this->sutun,(T)0);
	for(int i = 0; i < this->satir;i++)
		for(int j = 0;j < this->sutun;j++)
			m.dizi[i][j] = this->dizi[i][j] % y;
		return m;
}
//"^" operatörü için overload
template <class T>
Matrix<T> Matrix<T>::operator^(int u)
{
	Matrix<T> m(this->satir,this->sutun,(T)0);
	for(int i = 0;i<this->satir;i++)
		for(int j=0;j<this->sutun;j++)
			{
				int l = 1;
				for(int k = 0;k<u;k++)
					l *= this->dizi[i][j];
				m.dizi[i][j] = l;
			} 
			return m;
}
//"=" operatörü için overload
template <class T>
void Matrix<T>::operator=(const Matrix<T> &d)
{
	for(int i = 0;i<this->satir;i++)
		for(int j = 0;j<this->sutun;j++)
			this->dizi[i][j] = d.dizi[i][j];
}
//iki matris için "+" operatör overload işlemi
template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &mat)
{
	if(this->satir != mat.satir ||this->sutun != mat.sutun)
	{
		throw invalid_argument("Matris boyutları aynı olmalıdır!");
	}

	Matrix<T> m(this->satir,this->sutun,(T) 0);
	for(int i = 0; i < this->satir;i++)
		{
			for(int j = 0;j < this->sutun;j++)
			{
				m.dizi[i][j] = this->dizi[i][j] + mat.dizi[i][j];
			}
		}
		return m;

}
//iki matris için "-" operatör overload işlemi
template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &mat)
{
		if(this->satir != mat.satir ||this->sutun != mat.sutun)
		{
			throw invalid_argument("Matris boyutları aynı olmalıdır!");
		}

		Matrix<T> m(this->satir,this->sutun,(T)0);
		for(int i = 0; i < this->satir;i++)
			{
				for(int j = 0;j < this->sutun;j++)
				{
					m.dizi[i][j] = this->dizi[i][j] - mat.dizi[i][j];
				}
			}
		return m;

}
//iki matris için "*" operatörü overload işlemi
template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &mat)
{
	//ilk matrisin sutunu ile ikinci matrisin satırının aynı olması
	if(this->sutun != mat.satir)
	{
		throw invalid_argument("Matris boyutları uyumsuz!");
	}

	Matrix<T> m(this->satir,mat.sutun,(T)0.0);
	for(int i = 0; i < this->satir;i++)
	{
		for(int j = 0;j < mat.sutun;j++)
		{
			for(int k = 0;k<this->sutun;k++)
				m.dizi[i][j] += this->dizi[i][k] * mat.dizi[k][j]; 
		}
	}
	return m;

}
//Eleman düzeyinde çarpma işlemi yapıyor.
template <class T>
Matrix<T> Matrix<T>::emul(const Matrix<T> &em)
{
	//bu işlem için satir ve sutun sayıları aynı olmalıdır.
	if(this->satir != em.satir && this->sutun != em.sutun)
	{
		throw invalid_argument("Eleman çarpma yapılamaz!");
	}

	Matrix<T> m(this->satir,this->sutun,(T)0);
	for(int i = 0; i < this->satir;i++)
		for(int j = 0;j < this->sutun;j++)
				m.dizi[i][j] = this->dizi[i][j] * em.dizi[i][j]; 
	
			/*for(int k=0;k<this->satir;k++)
				for(int l=0;l<this->sutun;l++)
					this->dizi[k][l] = m.dizi[k][l];*/
	return m;
}
//determinant ve inv fonskiyonları için kullanılacak.
template <class T>
Matrix<T> Matrix<T>::cofactor(int rw,int cl)
{
	Matrix<T> values(satir - 1, sutun - 1 , (T)0);

	for (int i = 0,ii = 0; i < satir; i++)
    {
        if(i == rw)
      		continue;
    	for(int j = 0, jj = 0; j < satir; j++)
    	{
    		 if(j == cl)
      	{
       		continue;
      	}
      	else
      	{

        	values.dizi[ii][jj] = dizi[i][j];
        	jj++;

    	}
    }
    		ii++;
  	}
        
        return values;
}
//Matris'in determinantını hesaplayan fonksiyon
template <class T>
double Matrix<T>::determinant()
{
	//Determinant işlemi için kare matris olmalı
	if(this->satir != this->sutun)
	{
		throw invalid_argument("Determinant hesaplanamaz");
	}
	double det = 0.00;
	if(satir == 1)
	{
		return dizi[0][0];
	}
	else if(satir == 2)
	{
		return (dizi[0][0]*dizi[1][1]) - (dizi[0][1]*dizi[1][0]);
	}

    int a;
    int i = 0;
    for (int j = 0; j < sutun; j++)
    {
        if((i+j)%2 == 0) 
        {
            a = 1;
        }
        else 
   		{
            a = -1;
        }
        //the recursive call 
        det += ((dizi[i][j])*(a)*(cofactor(0, j).determinant())); 
    }
      return det;
}
//Matrisin tersini hesaplayan fonksiyon
template <class T> 
Matrix<double> Matrix<T>::inv()
{
	double det = this->determinant();
	if(det == 0.0)
	{
		throw invalid_argument("Bu matrisin tersi olamaz");
	}
	else
	{
		Matrix<double> inv(this->satir,this->sutun,0.0);
		for(int i = 0;i<satir;i++)
			for(int j = 0;j<sutun;j++)
				inv.setItem(i,j,(((this->transpoze()).cofactor(i,j)).determinant()/
					det));
		return inv;
	}
}
//Image sınıfı için gerekli değerleri içeren struct
struct RGB 
{
	// r = red,g = green,b = blue;
	int r,g,b;
};
class Image : public Matrix<RGB>
{
	public:
		Image();
		Image(int satir,int sutun);
		Image(string,string);
		void color2gray();
		void imRead(string,string);
		void imWrite(string,string);
		void gray2binary(int);
		void erosion();
		void dilation();
		void opening();
		void closing();
};
//255x255 boyutunda, piksel değerleri "0";
Image::Image() : Matrix(255,255,RGB())
{
	for(int i=0;i<255;i++)
		for(int j =0;j<255;j++)
		{
			dizi[i][j].r = 0;
			dizi[i][j].g = 0;
			dizi[i][j].b = 0;
		}
};
 //(str x stn) görüntü boyutunda, varsayılan piksel değerleri 0
Image::Image(int str,int stn) : Matrix(str,stn,RGB())
{
	for(int i=0;i<str;i++)
		for(int j =0;j<stn;j++)
		{
			dizi[i][j].r = 0;
			dizi[i][j].g = 0;
			dizi[i][j].b = 0;
		}
};
Image::Image(string filename,string format):Matrix(1,1,RGB())
{	
	//görüntüyü dosyadan okuma için imRead() çağırılıyor.
	this->imRead(filename,format);
}
//dosyadan görüntü okuyan fonksiyon
void Image::imRead(string filename,string format)
{
	char* bfr;
	string dosyaAdi = filename + "." + format;
	ifstream dosya(dosyaAdi,ios::binary);
	if(dosya)
	{
		int str,stn;
		bfr = new char[1];
		dosya.read(bfr,1);
		str = (unsigned int)(unsigned char)(bfr[0]);
		dosya.read(bfr,1);
		stn = (unsigned int)(unsigned char)(bfr[0]);
		//cout<<str<<" "<<stn<<endl;
		//cout<<satir<<endl;
		resize(str,stn);
		for(int i = 0;i<this->satir;i++)
		{
			for(int j = 0;j<this->sutun;j++)
			{
				dosya.read(bfr,1);
				//cout<<i<<" "<<j<<endl;
				dizi[i][j].g = (unsigned int)(unsigned char)(bfr[0]);
			}
		}
	}
}
//dosyaya görüntü yazma
void Image::imWrite(string filename,string format)
{
	char* buf;
	string dosyaAdi = filename + "." + format;
	ofstream dosya(dosyaAdi,ios::binary);
	if(dosya)
	{
		buf = new char[1];
		buf[0] = (unsigned int)(unsigned char)(satir);
		dosya.write(buf,1);
		buf[0] = (unsigned int)(unsigned char)(sutun);
		dosya.write(buf,1);
		//cout<<satir<<" "<<sutun<<endl;
		//cout<<satir<<endl;
		for(int i = 0;i<this->satir;i++)
		{
			for(int j = 0;j<this->sutun;j++)
			{
				buf[0] = (unsigned int)(unsigned char)(dizi[i][j].g);
				dosya.write(buf,1);
				//cout<<i<<" "<<j<<endl;
			}
		}
	}
}
//renkli görüntüyü gri seviyeye çeviriyor.
void Image::color2gray()
{
	for(int i = 0;i<satir;i++)
		for(int j = 0;j<sutun;j++)
		{
			dizi[i][j].b = 0;
			dizi[i][j].r = 0;
			dizi[i][j].g = ((dizi[i][j].r) + (dizi[i][j].g) + 
				(dizi[i][j].b))/3;
		}
};
//gri görüntüyü eşik değerine bakarak ikili görüntüye çeviriyor.
void Image::gray2binary(int thr)
{
	for(int i = 0;i<this->satir;i++)
	{
		for(int j = 0;j<this->sutun;j++)
		{
			if(thr > dizi[i][j].g)
				this->dizi[i][j].g = 0;
			else
				this->dizi[i][j].g = 1;
		}
	}
}
//ikili görüntüye morfolojik erozyon yapıyor.
void Image::erosion()
{
	cout <<endl;
	Image temp(this->satir,this->sutun);
	for(int i = 1; i < satir - 1; i++)
	{
		for(int j = 1; j < sutun - 1; j++)
		{
			if(this->dizi[i][j].g == 0)
				continue;
			temp.dizi[i][j] = this->dizi[i][j];
			for(int k = i - 1;k <= i+1; k++)
			{
				for(int l = j - 1; l <= j + 1;l++)
				{
					if(this->dizi[k][l].g == 0)
					{
						temp.dizi[i][j].g = dizi[k][l].g;
						k = i + 1;
						break;
					}
				}
			}
		}
	}
	for(int i =0;i<sutun;i++)
	{
		dizi[0][i].g = 0;
	}
	for(int i =0;i<sutun;i++)
	{
		dizi[(this->satir)-1][i].g = 0;
	}
	for(int i =0;i<satir;i++)
	{
		dizi[i][0].g = 0;
	}
	for(int i =0;i<(this->sutun)-1;i++)
	{
		dizi[i][sutun-1].g = 0;
	}
	for(int i = 0;i<this->satir;i++)
	{
		for(int j = 0;j<this->sutun;j++)
		{
			this->dizi[i][j].g = temp.dizi[i][j].g;
			cout<<temp.dizi[i][j].g;
		}
		cout<<endl;
	}
}
//ikili görüntüye morfolojik genişleme yapıyor.
void Image::dilation()
{
	cout<<endl;
	Image temp(this->satir,this->sutun);
	for(int i = 0; i < satir; i++)
	{
		for(int j = 0; j < sutun; j++)
		{
			if(dizi[i][j].g == 1){
				temp.dizi[i][j].g = 1;
				continue;
			}
			for(int k = i - 1; k <= i + 1; k++)
			{
					if(k < 0 || k > this->satir - 1)
						continue;
				for(int l = j - 1; l <= j + 1; l++)
				{
					if(l < 0 || l > this->sutun - 1)
						continue;
					if(dizi[k][l].g == 1)
					{
						temp.dizi[i][j].g = dizi[k][l].g;
						k = i + 1;
						break;
					}
				}
			}
		}
	}
	for(int i = 0;i<this->satir;i++)
	{
		for(int j = 0;j<this->sutun;j++)
		{
			this->dizi[i][j].g = temp.dizi[i][j].g;
			cout<<this->dizi[i][j].g;
		}
		cout<<endl;
	}
}
void Image::opening()
{
	this->erosion();
	this->dilation();
}
void Image::closing()
{
	this->dilation();
	this->erosion();
}

template <class T>
class Table: public Matrix<int>
{
	public:
		Table();
		Table(int,int,int);
		Table(int,int,char);
		void print();
		int itemAt(int,int);
		int itemAt(string);
		int itemAt(string,string);
		void setRowNames(string s[],int);
		void setColNames(string s[],int);
	private:
		string* sutunAd;
		string* satirAd;
		void satirduzeltme();
};
//satir ve sutun isimlerine default değerleri atıyor.
template <class T>
void Table<T>::satirduzeltme()
{	
	this->satirAd = new string[this->satir];
	for(int i = 0;i<satir;i++)
		this->satirAd[i] = to_string(i);
	this->sutunAd = new string[this->sutun];
	for(int j = 0;j<sutun;j++){
		if(j+65<=90)
		this->sutunAd[j] = string(1,(char)(j+65));
	}
}
//10x10 boyutuna sahip 0 değerli matris oluşturuyor.
template <class T>
Table<T>::Table() : Matrix()
{
	satirduzeltme();
}
//rowxclmn boyutunda vrb değerli matris
template <class T>
Table<T>::Table(int row,int clmn,int vrb) : Matrix(row,clmn,vrb)
{
	satirduzeltme();
}
//ch'a bağlı olarak rowxcolumn boyutunda matris
template <class T>
Table<T>::Table(int row,int column,char ch) : Matrix(row,column,ch)
{
	satirduzeltme();
}
//[r,c] indisini geri döndürüyor.
template <class T>
int Table<T>::itemAt(int r,int c)
{
	cout<<dizi[r][c]<<endl;
	return dizi[r][c];
}
//belirtilen hücredeki değeri geri döndürüyor.
template <class T>
int Table<T>::itemAt(string s)
{
	int t1,t2;
	for(int i = 0;i<sutun;i++)
	{
		if(sutunAd[i] == string(1,s[0]))
		{
			t1 = i;
		}
	}
	for(int j = 0; j<satir;j++)
	{
		if(satirAd[j] == string(1,s[1]))
		{
			t2 = j;
		}
	}
	cout<<dizi[t2][t1]<<endl;
	return dizi[t2][t1];
}
//belirtilen hücredeki değeri geri döndürüyor.
template <class T>
int Table<T>::itemAt(string rs,string cs)
{
	int t1,t2;
	for(int j = 0; j<satir;j++)
	{
		if(!this->satirAd[j].compare(rs))
		{
			t1 = j;
		}
	}
	for(int i = 0;i<sutun;i++)
	{
		if(!this->sutunAd[i].compare(cs))
		{
			t2 = i;
		}
	}

	cout<<dizi[t1][t2]<<endl;
	return dizi[t1][t2];
}
//satir isimlerini düzenliyor.
template <class T>
void Table<T>::setRowNames(string s1[],int n)
{
	if(satir > n)
	{
		for(int i = 0;i<n;i++)
		{
			if(s1[i].length()>8)
			{
				satirAd[i] = s1[i].substr(0,8);
			}
			else
				satirAd[i] = s1[i];
		}
	}
	else
	{
		for(int i =0;i<satir;i++)
		{
			if(s1[i].length()>8)
			{
				satirAd[i] = s1[i].substr(0,8);
			}
			else
				satirAd[i] = s1[i];
		}
	}
}
//sutun isimlerini düzenliyor.
template <class T>
void Table<T>::setColNames(string s2[],int n)
{
	if(sutun > n)
	{
		for(int i = 0;i<n;i++)
		{
			if(s2[i].length()>4)
			{
				sutunAd[i] = s2[i].substr(0,4);
			}
			else
				sutunAd[i] = s2[i];
		}
	}
	else
	{
		for(int i =0;i<sutun;i++)
		{
			if(s2[i].length()>4)
			{
				sutunAd[i] = s2[i].substr(0,4);
			}
			else
				sutunAd[i] = s2[i];
		}
	}
}
//Tablo değerlerini satır ve sütun adlarıyla yazdırır
template <class T>
void Table<T>::print()
{
	cout<<setw(8)<<" ";
	for(int k = 0;k<sutun;k++) 
	{
		cout<<setw(4)<<sutunAd[k];
	}
	cout<<endl;
	for(int i =0;i<satir;i++)
	{
		cout<<setw(8)<<satirAd[i];
		for(int j = 0;j<sutun;j++)
		{
			cout<<setw(4)<<dizi[i][j];
		}
		cout<<endl;
	}
}
int main()
{
	return 0;
}
