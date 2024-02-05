#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

// mayinyerlestirme foksiyonumuz 15 mayinimizi 10*10 luk matrisimizde rastgele herhangi bir konuma uygun parametrelerle dagıtmamizi sağlamaktadır.
void mayinyerlestirme(char mayintarla[10][10]);

/* konumbelirtme fonksiyonumuz kullanıcı tarafından girilen satır sütun bilgisine göre açılan nokta için tepki verir 
yani oyunu kullanıcı bu fonksiyonda somutsal sekilde kullanır. */
int konumbelirtme(char mayintarla[10][10]);

//tarlayazdır fonsiyonumuz oluşturulan matris dizisini ekrana bastırır.
void tarlayazdir(char tarla[10][10]);

//tarlaboslukdoldur fonskiyonumuz tarlamızın ilk hali için dizimizdeki tüm elemanları '-' karakteriyle doldurarak boşlukları niteler.
void tarlaboslukdoldur(char tarla[10][10]);

//karemayinsayiyazdir fonksiyonumuz dizimizdeki karelerin üstündeki mayin sayisini hesaplayıp ekrana yazdırır.
void karemayinsayiyazdir(char mayintarla[10][10]);

/*aynınoktaengelleme fonksiyonu oyunu oynarken önceden açtığımız herhangi bir noktayı bir kez daha açmamamızı engellemektedir.
(bu fonksiyon olmadığında oyunu aynı noktalara tekrar tekrar basarak kazanma olasılığımız bulunuyordu.)
Böylelikle oyunu daha oynanabilir ve gerçekçi hale getirmektedir
 */
int ayninoktaengelleme(int sat,int sut,char noktatarla[10][10]);

int main() {
    int secim=1;
    char mayintarla[10][10];

    while(secim==1){
    	tarlaboslukdoldur(mayintarla);
        mayinyerlestirme(mayintarla);
        secim=konumbelirtme(mayintarla);
    }
    return 0;
}

void mayinyerlestirme(char mayintarla[10][10]) {
	
    char satirmayin[10],sutunmayin[10];
    int sutunmayinsayi,satirmayinsayi,i,j,mayinsayi=0,k;

    srand(time(NULL));

    while(mayinsayi!=15) {

        k=rand()%100+1;

        // bu döngü tüm satırlarda ve sütunlarda bulunan mayın sayılarını  sutunmayın ve satırmayın dizilerinde saklamaktadır.
	for(i=0;i<10;i++) {
	    sutunmayinsayi=0;
	    satirmayinsayi=0;
 
            for(j=0;j<10;j++) {
  
                if(mayintarla[i][j]=='*'){	
  	            satirmayinsayi+=1;
  		}
   		if(mayintarla[j][i]=='*') {
     		    sutunmayinsayi+=1; 
		} 
	    }
  	sutunmayin[i]=sutunmayinsayi;
  	satirmayin[i]=satirmayinsayi;
	}
  	i=rand()%10;
  	j=rand()%10;

	//k sayısını kullanmamın sebebi rastgele atanan sayıyı uzun zaman aralıklarıyla atamamk(mayınların sürekli olarak yakınlığını engellemek)
	//Mayınlar uygun parametrelerle döşenmektedir.
	if(((((k%2==0 && sutunmayin[j]<3 ) && satirmayin[i]<3 )&& mayintarla[i][j-1]!='*' )&&mayintarla[i][j+1]!='*') 
		&&(mayintarla[i-1][j-1]!='*' && (mayintarla[i-1][j+1]!='*' &&( mayintarla[i+1][j+1]!='*' 
		&&(mayintarla[i+1][j]!='*' && (mayintarla[i-1][j]!='*' && mayintarla[i+1][j-1]!='*')))))) {
		
	    if(mayintarla[i][j]!='*') {
	        mayintarla[i][j]='*';
                mayinsayi+=1;  
	    }
	}
    }
}

int konumbelirtme(char mayintarla[10][10]) {

    char bostarla[10][10];
    char noktatarla[10][10];
    int sat,sut,secim,sonuc,skor,nokta;
    skor=0;
    sonuc=1;
	
    tarlaboslukdoldur(noktatarla);
    printf("\t\t<<<<< ALT & MINEFIELD >>>>>\n\n\t\t");
	
    for(int i=0;i<85;i++) {
        tarlaboslukdoldur(bostarla);
        tarlayazdir(bostarla);
        karemayinsayiyazdir(mayintarla);
    
        do{
            printf("\nLutfen satir ve sutun konumunu uygun sekilde giriniz(Satir Sutun):");
            scanf("%d %d",&sat,&sut);
            nokta=ayninoktaengelleme(sat,sut,noktatarla);
        }while((((sat>10 || sat<1)||(sut>10 || sut<1))) || nokta==0);
 
        if(mayintarla[sat-1][sut-1]=='-'){
    	    system("CLS");
	    skor+=1;
 
 	    if(skor!=85) {
 	        printf("\t\t<<<<< ALT & MINEFIELD >>>>>\n\n\t\t");	
                printf("Ah!! ucuz kurtulduk adamim.Haydi Gidelim!\n\n\t\t");
	    }
        }
        if(mayintarla[sat-1][sut-1]=='*') {
            system("CLS");
 	    printf("\t\t<<<<< ALT & MINEFIELD >>>>>\n\n\t\t");
	    tarlayazdir(mayintarla);
	    printf("\n\nLanet olsun adamim olmek icin cok genctim :/\n");
 	    sonuc=0;
 	    break;
        }
    }
	
    if(sonuc==1) {
        tarlayazdir(mayintarla);	
        printf("\nBravo adamim kazandin!! seninle oynamak cok buyuk keyifti..\n\n");

        do{
            printf("Tekrar oynamaya ne dersin?(1=Evet:0=Hayir):");	
	    scanf("%d",&secim);
        }while(secim<0 || secim>1);

        if(secim==0){
	    printf("\nPekalaa Gorusmek uzere..");
        }
        if(secim==1) {
            system("cls");
	    printf("Tekrar Hosgeldin Brocum\n\n");
        }
    }
	
    if(sonuc==0) {
        if(skor<=5) {
            printf("Dostum sen de ne kadar sanssizsin bee!\n\n");}
        else if(skor>5 && skor<50) {
	    printf("Biraz daha oynamaya ihtiyacin var gibi..\n\n"); 
        }
        else{
            printf("Bu kadar yaklasmisken kazanmak icten bile degildi..\n\n"); 
        }
	    
        do{
	    printf("Tekrar oynamaya ne dersin?(1=Evet:0=Hayir):");	
	    scanf("%d",&secim);
        }while(secim<0 || secim>1);

        if(secim==0){
	    printf("\nPekalaa Gorusmek uzere..");
        }
        if(secim==1) {
	    system("cls");
	    printf("Tekrar Hosgeldin Brocum\n\n");
        }
    }
    return secim; 
}

void tarlayazdir(char tarla[10][10]) {

    for(int i=0;i<10;i++) {

        for(int j=0;j<10;j++){
            printf("%c  ",tarla[i][j]);
        }
        printf("\n\t\t");
    }
}

void tarlaboslukdoldur(char tarla[10][10]) {
    int mayinsayisi=0;	

    for(int i=0;i<10;i++) {
 
        for(int j=0;j<10;j++) {
            tarla[i][j]='-'; 
        }
    }
}

void karemayinsayiyazdir(char mayintarla[10][10]) {
    char karemayin[5];	
    int mayinsayi;
	
    for(int k=0;k<5;k++) {
        mayinsayi=0; 
        for(int i=k;i<10-k;i++) {
	 
	    if(i==k || i==9-k) {
	 
	        for(int j=k;j<10-k;j++) { 
	  
	            if(mayintarla[i][j]=='*') {
	                mayinsayi+=1;
                    }
                }	 
            }
            else {  
	   
                for(int j=k;j<10-k;j=j+9-2*k){
	
                    if(mayintarla[i][j]=='*') {
         	        mayinsayi+=1;
                    }
                }	 	 
            }	 
        }	     
    karemayin[k]=mayinsayi;  	
    }
    printf("\nBuyuk kareden kucuk kareye dogru>>:\n");
    for(int i=0;i<5;i++) {
  
        if(karemayin[i]!=0) {
            printf("%d.Karedeki Mayin Sayisi=%d\n",i+1,karemayin[i]);
        }
    } 
} 

int ayninoktaengelleme(int sat,int sut,char noktatarla[10][10]) {
    int nokta;
    
    if(noktatarla[sat-1][sut-1]=='*') {
        printf("\nBu noktayi daha once girmistiniz zaten!!");  
        nokta=0; 
    } 
    if(noktatarla[sat-1][sut-1]!='*') {
        noktatarla[sat-1][sut-1]='*';
        nokta=1;  
    }
    return  nokta;
}
