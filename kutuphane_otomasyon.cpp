#include <iostream>
#include <fstream> //Dosya islemleri için kullanilan kütüphane
#include <iomanip>
#include <string>
using namespace std;
//Kira Sinifi Basliyor
class kira
{
public:
    string alici_adi;
    string kitap_adi;
    int isbn_no; //Kitaplar için kullanilan numaralandirma sistemi
    string alinma_tarihi;

    void kira_gir();
    void kira_yazdir();
};

void kira::kira_gir()
{
    cout<<"Kitabi Alanin Adi: ";
    cin>>alici_adi;
    cout<<"Kitabin Adi: ";
    cin>>kitap_adi;
    cout<<"Kitabin ISBN Numarasi: ";
    cin>>isbn_no;
    cout<<"Kitabin Alinma Tarihi: ";
    cin>>alinma_tarihi;
}

void kira::kira_yazdir()
{
    cout<<"Kitabi Alanin Adi: "<<alici_adi<<endl;
    cout<<"Kitabin Adi: "<<kitap_adi<<endl;
    cout<<"Kitabin ISBN Numarasý: "<<isbn_no<<endl;
    cout<<"Kitabin Alinma Tarihi: "<<alinma_tarihi<<endl;
}

//Kira Sinifi Bitti
//Kitap Sinifi Basladi

class kitap
{
public:
    string alici_adi;
    string kitap_yazari;
    float kitap_fiyati;
    int isbn_no;

    void kitap_gir();
    void kitap_yazdir();
};

void kitap::kitap_gir()
{
    cout<<"Kitabin Adi: ";
    cin>>alici_adi;
    cout<<"Kitabin Yazari: ";
    cin>>kitap_yazari;
    cout<<"Kitabin Fiyati: ";
    cin>>kitap_fiyati;
    cout<<"Kitanin ISBN Numarasi: ";
    cin>>isbn_no;
}

void kitap::kitap_yazdir()
{
    cout<<"Kitabin Adi: "<<alici_adi<<endl;
    cout<<"Kitabin Yazari: "<<kitap_yazari<<endl;
    cout<<"Kitabin Fiyati: "<<kitap_fiyati<<endl;
    cout<<"Kitabin ISBN Numarasi: "<<isbn_no<<endl;
}

//Kitap Sinifi Bitti
//Kutuphane Sinifi Basladi 106 546

class kutuphane
{
 private:
        fstream dosyasi; //dosya giris çikis islemleri icin fstream kullanilir.
        fstream yedek;
        fstream kirasi;

        void kira_ac()
        {
            kirasi.open("kitap_kirasi.txt",ios::out|ios::in|ios::app); //daha cok dosya acma, yazma islemleri icin kullanılır
            //kirasi.setf; //tek parametre
        }
        void kira_kapat()
        {
            kirasi.close();
        }
        void dosya_ac()
        {
            dosyasi.open("kitap_kayit.text",ios::out|ios::in|ios::app);
            //yedek.setf;
        }
        void yedek_ac()
        {
            yedek.open("yedek_dosya.txt",ios::out|ios::in|ios::app);
            //yedek.setf;
        }
        void dosya_kapat()
        {
            dosyasi.close();
        }
        void yedek_kapat()
        {
            yedek.close();
        }

        void dosyadan_kitap_oku(kitap &temp)
        {
            dosyasi>>temp.alici_adi;
            dosyasi>>temp.kitap_yazari;
            dosyasi>>temp.kitap_fiyati;
            dosyasi>>temp.isbn_no;
        }

        void dosyaya_kitap_yaz(kitap &k)
        {
            dosyasi<<endl
            <<setw(50)<<k.alici_adi
            <<setw(50)<<k.kitap_yazari
            <<setw(50)<<k.kitap_fiyati
            <<setw(50)<<k.isbn_no;
        }

        void kiradan_kitap_oku(kira &temp)
        {
            kirasi>>temp.alici_adi;
            kirasi>>temp.kitap_adi;
            kirasi>>temp.isbn_no;
            kirasi>>temp.alinma_tarihi;
        }

        void kiraya_kitap_yaz(kira &k)
        {
            kirasi<<setw(50)<<k.alici_adi
            <<setw(50)<<k.kitap_adi
            <<setw(50)<<k.isbn_no
            <<setw(50)<<k.alinma_tarihi;
        }

        void yedek_kitap_yaz(kitap &k)
        {
            yedek<<setw(50)<<k.alici_adi
            <<setw(50)<<k.kitap_yazari
            <<setw(50)<<k.kitap_fiyati
            <<setw(50)<<k.isbn_no<<endl;
        }

        void kiraya_yedek_yaz(kira &k)
        {
            yedek<<setw(50)<<k.alici_adi
            <<setw(50)<<k.kitap_adi
            <<setw(50)<<k.isbn_no
            <<setw(50)<<k.alinma_tarihi;
        }
 public:
    kira k;
    kitap kp;
    int sayac;
    kutuphane ()
    {
       kitap_goster();
       system("cls");
    }
void kira_ekle()
{
	kira_ac();
	k.kira_gir();
	kiraya_kitap_yaz(k);
	kira_kapat();
}
void kitap_ekle()
{
	dosya_ac();
	kp.kitap_gir();
	dosyaya_kitap_yaz(kp);
	dosya_kapat();
	sayac++;
}
int kitap_bul(int isbn_no)
{
	dosya_ac();
	kitap temp;
	for(int i=1;i<sayac;i++)
	{
		dosyadan_kitap_oku(temp);
		if(temp.isbn_no==isbn_no){
			temp.kitap_yazdir();
			dosya_kapat();
			return 0;
		}
	}
	dosya_kapat();
	cout<<"Aradiginiz ISBN Numarali Kitap Bulunamadı...";
	return 0;
}
void kirayi_goster()
{
	kira_ac();
	kira temp;
	kiradan_kitap_oku(temp);
	while(!dosyasi.eof())//eof dosya sonuna ulaşıp ulaşmadıgına bakar
	{
		temp.kira_yazdir();
		kiradan_kitap_oku(temp);
	}
	kira_kapat();
}
void kitap_goster()
{
	sayac=0;
	dosya_ac();
	kitap temp;
	if(!dosyasi.eof()){
		sayac++;
	}
	dosyadan_kitap_oku(temp);
	while(!dosyasi.eof())
	{
		temp.kitap_yazdir();
		dosyadan_kitap_oku(temp);
		sayac++;
	}
	dosya_kapat();
}
void kitap_sayisi()
{
	system("cls");
	cout<<"Kitapliginiz da Bulunan Kitap Sayisi"<<sayac-1<<"'dir..";
}
void kitap_sil(int isbn_no)
{
	dosya_ac();
	yedek_ac();
	kitap temp;
	for(int i=1;i<sayac;i++)
	{
		dosyadan_kitap_oku(temp);
		if(temp.isbn_no==isbn_no)
		{
			cout<<"Silmek Istedeginiz Kitap Bulundu ve Silindi..";
			sayac--;
		}
		else{
			yedek_kitap_yaz(temp);
		}
	}
	dosya_kapat();
	remove("kitap_kayit.txt");
	yedek_kapat();
	rename("yedek_dosya.txt","kitap_kayit.txt");
}
void kiradan_sil(int isbn_no)
{
	kira_ac();
	yedek_ac();
	kira temp;

	for(int i=1;i<sayac;i++)
	{
		kiradan_kitap_oku(temp);
		if(temp.isbn_no==isbn_no)
		{
			cout<<"Silmek Istediginiz Kitap Bulundu ve Silindi..";
			sayac--;
		}
		else{
			kiraya_yedek_yaz(temp);
		}
	}
	dosya_kapat();
	remove("kitap_kira.txt");
	yedek_kapat();
	rename("yedek_dosya.txt","kitap_kira.txt");
}
	void isbn_gore_sirala()
	{
		dosya_ac();
		yedek_ac();
		kitap temp[100];
		kitap gecici;
		for(int i=0;i<sayac-1;i++)
		{
			dosyadan_kitap_oku(temp[i]);
		}
		for(int i=0;i<sayac-1;i++)
		{
			for(int j=i+1;j<sayac-1;j++)
			{
				if(temp[j].isbn_no<temp[i].isbn_no)
				{
					gecici=temp[i];
					temp[i]=temp[j];
					temp[j]=gecici;
				}
			}
		}
		for(int i=0;i<sayac-1;i++)
		{
			yedek_kitap_yaz(temp[i]);
		}
		dosya_kapat();
		remove("kitap_kayit.txt");
		yedek_kapat();
		rename("yedek_dosya.txt","kitap_kira.txt");
		cout<<"ISBN Numarasına Gore Siralama Islemi Basarıyla Gerceklestirildi..";
	}
    void ada_gore_sirala()
    {
        dosya_ac();
        yedek_ac();
		kitap temp[100];
		kitap gecici;
		for(int i=0;i<sayac-1;i++)
		{
			dosyadan_kitap_oku(temp[i]);
		}
		for(int i=0;i<sayac-1;i++)
		{
			for(int j=i+1;j<sayac-1;j++)
			{
				if(temp[j].alici_adi<temp[i].alici_adi)
				{
					gecici=temp[i];
					temp[i]=temp[j];
					temp[j]=gecici;
				}
			}
		}
		for(int i=0;i<sayac-1;i++)
		{
			yedek_kitap_yaz(temp[i]);
		}
		dosya_kapat();
		remove("kitap_kayit.txt");
		yedek_kapat();
		rename("yedek_dosya.txt","kitap_kayit.txt");
		cout<<"İsme Gore Siralama Islemi Basariyla Gerceklestirildi..";
	}

	void yazara_gore_sirala()
	{
		dosya_ac();
		yedek_ac();
		kitap temp[100];
		kitap gecici;
		for(int i=0;i<sayac-1;i++)
		{
			dosyadan_kitap_oku(temp[i]);
		}
		for(int i=0;i<sayac-1;i++)
		{
			for(int j=i+1;j<sayac-1;j++)
			{
				if(temp[j].kitap_yazari<temp[i].kitap_yazari)
				{
					gecici=temp[i];
					temp[i]=temp[j];
					temp[j]=gecici;
				}
			}
		}
		for(int i=0;i<sayac-1;i++)
		{
			yedek_kitap_yaz(temp[i]);
		}
		dosya_kapat();
		remove("kitap_kayit.txt");
		yedek_kapat();
		rename("yedek_dosya.txt","kitap_kayit.txt");
		cout<<"Yazara Gore Siralama Islemi Basariyla Gerceklestirildi..";
	}

	void fiyata_gore_sirala()
	{
		dosya_ac();
		yedek_ac();
		kitap temp[100];
		kitap gecici;
		for(int i=0;i<sayac-1;i++)
		{
			dosyadan_kitap_oku(temp[i]);
		}
		for(int i=0;i<sayac-1;i++)
		{
			for(int j=i+1;j<sayac-1;i++)
			{
				if(temp[j].kitap_fiyati<temp[i].kitap_fiyati)
				{
					gecici=temp[i];
					temp[i]=temp[j];
					temp[j]=gecici;
				}
			}
		}
		for(int i=0;i<sayac-1;i++)
		{
			yedek_kitap_yaz(temp[i]);
		}
		dosya_kapat();
		remove("kitap_kayit.txt");
		yedek_kapat();
		rename("yedek_dosya.txt","kitap_kayit.txt");
		cout<<"Fiyata Gore Siralama Islemi Basarıyla Gerceklestirildi..";
	}
};

//Kutuphane Sinifi Bitti
//Menu Sinifi Basladi

class Menu
{
public:
    string kitaplarim();
    string menu();
    string kirala();
    //void about(); //hakkinda
    string siralama();
};

string Menu::menu()
{
    string tercih; //choice
    cout<<"-**-**-**-**-**-**-**-**-**-**-"<<endl;
    cout<<"1)Kitaplarım"<<endl;
    cout<<"2)Kiralama Islemleri"<<endl;
    cout<<"3)Cikis"<<endl;
    cout<<"-**-**-**-**-**-**-**-**-**-**-"<<endl;
    cout<<"Lütfen Bir Secenek Seciniz: ";
    cin>>tercih;

return tercih;
}

string Menu::kirala()
{
    string tercih;
    cout<<"-**-**-**-**-**-**-**-**-**-**-"<<endl;
    cout<<"1)Kiraya Kitap Ekle"<<endl;
    cout<<"2)Kiradan Kitap Sil"<<endl;
    cout<<"3)Kirada ki Kitaplar"<<endl;
    cout<<"-**-**-**-**-**-**-**-**-**-**-"<<endl;
    cout<<"Lütfen Bir Seçenek Seçiniz: "<<endl;
    cin>>tercih;

return tercih;
}

string Menu::kitaplarim()
{
    string tercih;
    cout<<"-**-**-**-**-**-**-**-**-**-**-"<<endl;
    cout<<"1)Kitap Ekle"<<endl;
    cout<<"2)Kitap Bul"<<endl;
    cout<<"3)Kitap Sil"<<endl;
    cout<<"4)Kitap Sirala"<<endl;
    cout<<"5)Kitap Listesini Goster"<<endl;
    cout<<"-**-**-**-**-**-**-**-**-**-**-"<<endl;
    cout<<"Lütfen Bir Secenek Seciniz: ";
    cin>>tercih;

return tercih;
}

string Menu::siralama()
{
    string tercih;
    cout<<"-**-**-**-**-**-**-**-**-**-**-"<<endl;
    cout<<"1)Isme Gore Siralama"<<endl;
    cout<<"2)Yazara Gore Siralama"<<endl;
    cout<<"3)Fiyata Gore Siralama"<<endl;
    cout<<"4)ISBN Numarasina Gore Siralama"<<endl;
    cout<<"-**-**-**-**-**-**-**-**-**-**-"<<endl;
    cout<<"Lütfen Bir Secenek Seciniz: ";
    cin>>tercih;

return tercih;
}

//Menu Sinifi Bitti

int main()
{
    setlocale(LC_ALL,"Turkish");
    kutuphane a;
    Menu b;
int isbn;
for(;;)
{
    string tercih_b=b.menu();
    if(tercih_b=="1"){
         tercih_b=b.kitaplarim();
         if(tercih_b=="1"){
         a.kitap_ekle();
         }
         if(tercih_b=="2"){
            cout<<"Bulmak Istediginiz Kitabin ISBN Numarasını Giriniz: ";
            cin>>isbn;
            a.kitap_bul(isbn);
         }
         if(tercih_b=="3"){
            cout<<"Silmek Istediginiz Kitabin ISBN Numarasını Giriniz: ";
            cin>>isbn;
            a.kitap_sil(isbn);
         }
         if(tercih_b=="5"){
            a.kitap_goster();
         }
         if(tercih_b=="4"){
            tercih_b=b.siralama();
            if(tercih_b=="1")
                a.ada_gore_sirala();
            if(tercih_b=="2")
                a.yazara_gore_sirala();
            if(tercih_b=="3")
                a.fiyata_gore_sirala();
            if(tercih_b=="4")
                a.isbn_gore_sirala();
         }
         /*if(tercih_b=="6")
          a.kitap_sayisi();*/
       }
       else if(tercih_b=="2")
       {
          tercih_b=b.kirala();
          if(tercih_b=="1")
            a.kira_ekle();
          if(tercih_b=="2")
          {
              cout<<"Silmek İstediğiniz Kitabin ISBN Numarasini Giriniz: ";
              cin>>isbn;
              a.kiradan_sil(isbn);
          }
          if(tercih_b=="3")
          {
              a.kirayi_goster();
          }
       }

       else if(tercih_b=="3")
        exit(1);
       else
       {
           system("cls"); //ekranda ki yazıları siler
           cout<<"Yanlis Bir Giris Yaptiniz.."<<endl;
           cout<<"Gecerli Bir Numara Giriniz";
       }
}
return 0;
}