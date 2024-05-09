// Paper Clock V2
//
// Author : Xenatronics
//
// Version : see library.properties
//
// License: GNU GENERAL PUBLIC LICENSE V3, see LICENSE
//
// include library, include base class, make path known
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <GxEPD.h>
#include <GxGDEH029A1/GxGDEH029A1.cpp>      // 2.9" b/w
#include <Fonts/Roboto15.h>
#include <Fonts/Roboto24.h>
#include <Fonts/Roboto64.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.cpp>
#include <GxIO/GxIO.cpp>
#include <simpleDSTadjust.h>
#include <WiFiManager.h> 
#include <MiniGrafx.h>

// Adjust according to your language
const String WDAY_NAMES[] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
const String MONTH_NAMES[] = {"Janvier ", "Fevrier ", "Mars ", "Avril ", "Mai ", "Juin ", "Juillet ", "Aout ", "Septembre ", "Octobre ", "Novembre ", "Decembre "};

// é = $ ; è=#; ë=&

  const char*angels1[]={"!Jour de l'an","Basile","*Genevi#ve","*Odilon",
  "Edouard","*M$laine","Raymond","Lucien",
  "*Alix","Guillaume","*Pauline","*Tatiana",
  "*Yvette","*Nina",  "R$mi", "Marcel",
  "*Roseline",  "*Prisca","Marius","S$bastien", 
  "*Agnès","Vincent","Banard","François de Sales",
  "!Conversion de Paul", "*Paule","*Ang#le","Thomas d'Aquin",
  "Gildas","*Martine","*Marcelle"};

  const char*angels2[]={"*Ella","Pr$sentation","Blaise","*V$ronique",
  "*Agathe","*Gaston","*Eug#nie","*Jacqueline",
  "*Apolline","Arnaud","Notre Dame de Lourdes","F$lix",
  "*B$atrice","Valentin",  "Claude", "*Julienne",
  "Alexis",  "*Bernadette","Gabin","*Aim$e", 
  "Damien","*Isabelle","Lazare","Modeste",
  "Rom$o", "Nestor","*Honorine","Romain"};

  const char*angels3[]={"Albin","Charles","Gwenol$","Rom$o",
  "Th$ophile","*Agn#s","*F$licit$","Ryan",
  "*Françoise","Vivien","*Rosine","*Justine",
  "*L$andre","*Eve",  "Louise", "*B$n$dicte",
  "Patrick",  "Cyrille","Joseph","*Alexandra", 
  "Cl$mence","*L$a","*R$becca","*Catherine",
  "Humbert", "*Larissa","Albert","Gontran",
  "*Gladys","Am$d$e","*Acace"};
  
  const char*angels4[]={"Hugues","*Sandrine","Richard","Isidore",
  "*Ir#ne","Marcellin","Jean-Baptiste de la Salle","*Julie",
  "Gautier","Fulbert","Stanislas","Jules",
  "*Ida","Maxime",  "Paterne", "Benoit-Joseph",
  "*Anicet",  "Parfait","*Emma","*Odette", 
  "Anselme","Alexandre","Georges","Fid#le",
  "Marc", "*Alida","*Zita","*Val$rie",
  "Catherine de Sienne","Robert"};
  
  const char*angels5[]={"!Fête du travail","Boris","Philippe-Jacques","Sylvain",
  "*Judith","*Prudence","*Gis#le","!Armistice 1945",
  "!Pac*me","*Solange","*Estelle","Achille",
  "*Rolande","Mathias",  "*Denise", "Honor$",
  "Pascal",  "Eric","Yves","Bernardin", 
  "Constantin","Emile","Didier","Donatien",
  "*Sophie", "B$renger","Augustin","Germain",
  "Aymar","Ferdinand","!Visitation de la Ste Vierge"};
  
  const char*angels6[]={"Justin","Alcide",
  "Kevin","*Clothide","Boniface","Claude","Gilbert","M$dard","Ephrem",
  "Landry","Barnab$","Guy","Antoine","*Elis$e","*Germaine","R$gis",
  "Herv$","*L$once","*Jude","*Silv#re","Louis","Alban","*Audrey",
  "Jean","Prosper","Anthelme","Fernand","*Ir$n$e","Pierre","Martial"};

   const char*angels7[]={"Thierry","*Eug$nie","Thomas","*Isabelle","Antoine-Marie","*Maria","Roger",
  "*Priscille","*Irma","Ulric","Benoit","Olivier","Henri","Camille",
  "boneaventure","*Carmen","*Charlotte","Fr$d$ric"," ","Aur#le","Victor",
  "*Madeleine","*Brigitte","*Christine","Christophe","*Anne","F$lix","Samson",
  "*Marthe","*Juliette","Ignace"};

  const char*angels8[]={"Alphonse","Julien","*Lydie","*Darcy",
  "Abel","Sauveur","Ga&tan",  "Dominique","*B$n$dicte","Laurent","*Claire",
  "*Chantal","Hyppolyte","Maximilien",  "Assomption","*Armel","*Hyacinthe",
  "Eudes"," ","Bernard","Christophe", "*Marie-Reine","*Rose","Barth$l$my","Louis",
  "C$saire","*Monique","Augustin", "*Sabine","Fiacre","Aristide"};

   const char*angels9[]={"Gilles","*Ingrid","Gr$goire","*Rosalie",
  "*Raïssa","Bertrand","*Reine","!Nativit$",
  "Alain","*In#s","Adelphe","Apollinaire",
  "Aim$","!Croix Glorieuse",  "Roland",  "*Edith",
  "Renaud",  "*Nad#ge","*Emilie","Davy", 
  "Matthieu", "Maurice","!Automne","Th#cle",
  "Hermann","Côme et Damien","Vincent de Paul","Venceslas",
  "Michel","J$rôme"};

 const char*angels10[]={"Th$r#se de l'Enfant J$sus","L$ger","G$rard","François d'Assise",
  "*Fleur","Bruno","Serge","*P$lagie",
  "Denis","*Ghislaine","Firmin","Wilfried",
  "G$raud","Juste",  "*Th$r#se d'Avila",  "*Edwige",
  "Baudoin",  "Luc","Ren$","*Adeline", 
  "*C$line","*Elodie","Jean de Capistran","Florentin",
  "Cr$pin", "Dimitri","*Emeline","Jude",
  "Narcisse","Bienvenue","Quentin"};

const char*angels11[]={"!Toussaint","!D$funts","Hubert","Hubert","Charles",
  "Sylvie","Bertille","Carine","Geoffroy",
  "Th$odore","L$on","!Armistice 1918","Christian",
  "Brice","Sidoine",  "Albert", "*Marguerite",
  "*Elisabeth",  "Aude","Tanguy","Edmond", 
  "!Pr$sence de Marie","*C$cile","Cl$ment","*Flora",
  "*Catherine", "*Delphine","S$vrin","Jacques de la Marche",
  "Saturnin","Andr$"};

  const char*angels12[]={"*Florence","*Viviane","François Xavier","*Barbara",
  "G$rald","Nicolas","Ambroise","!Immacul$e Conception",
  "Pierre Fourier","Romaric","Daniel","!Jeanne-Françoise de Chan",
  "*Lucie","Gatien",  "*Ninon", "*Alice",
  "Ga&l",  "*Aude","Armand","*Ad#le", 
  "!Hiver","*Françoise Xavi#re","Cl$ment","*Flora",
  "!No&l", "Etienne","Jean","Innocents",
  "David","Roger","Sylvestre"};
                               
long lastDownloadUpdate = millis();
const int UPDATE_INTERVAL_SECS = 30 * 60; // Update every 10 minutes
// Change for 12 Hour/ 24 hour style clock
bool IS_STYLE_12HR = false;
// change for different ntp (time servers)
#define NTP_SERVERS "0.ch.pool.ntp.org", "1.ch.pool.ntp.org", "2.ch.pool.ntp.org"
#define UTC_OFFSET +1
struct dstRule StartRule = {"CEST", Last, Sun, Mar, 2, 3600}; // Central European Summer Time = UTC/GMT +2 hours
struct dstRule EndRule = {"CET", Last, Sun, Oct, 2, 0};       // Central European Time = UTC/GMT +1 hour
simpleDSTadjust dstAdjusted(StartRule, EndRule);
time_t dstOffset = 0;
 struct tm * timeinfo; 

GxIO_Class io(SPI, /*CS=D8*/ D1, /*DC=D3*/0 ,/*RST=D4*/ D4,D2); // arbitrary selection of D3(=0), D4(=2), selected for default of GxEPD_Class
GxEPD_Class display(io /*RST=D4*/ /*BUSY=D2*/); // default selection of D4(=2), D2(=4)
uint16_t palette[] = {ILI9341_BLACK, ILI9341_WHITE }; //3

char st[80];

void showFont(const char name[], const GFXfont* f)
{ 
  display.setFont(f);
  display.println(name); 
}

void configModeCallback (WiFiManager *myWiFiManager) {  
  Serial.println("Choisir AP");
  delay(3000);  
}

void updateData() {  
  configTime(UTC_OFFSET * 3600, 0, NTP_SERVERS);
  while(!time(nullptr)) {
    Serial.print("#");
    delay(100);
  }
  // calculate for time calculation how much the dst class adds.
  dstOffset = UTC_OFFSET * 3600 + dstAdjusted.time(nullptr) - time(nullptr);
  Serial.printf("Time difference for DST: %d", dstOffset);
}

const char * FormatSaint(const char * saint)
{   
   if(saint[0]=='*')
   {
      strcpy(st,"Ste ");     
      strncat(st,&saint[1],strlen(saint)+3);
   }
   else if (saint[0]=='!')
   {
      strcpy(st,"");
      strncat(st,&saint[1],strlen(saint));
   }
   else
   {
     strcpy(st,"St ");
     strncat(st,saint,strlen(saint)+2);
   }
   //Serial.print("Ange :");
   //Serial.println(st);
   return st; 
}
const char * GetSaint( struct tm *timeinfo)
{  
  if (timeinfo->tm_mon==0){
   return FormatSaint(angels1[timeinfo->tm_mday-1]);
  }
  if (timeinfo->tm_mon==1){
   return FormatSaint(angels2[timeinfo->tm_mday-1]);
  }
  if (timeinfo->tm_mon==2){
   return FormatSaint(angels3[timeinfo->tm_mday-1]);
  }  
  if (timeinfo->tm_mon==3){
   return FormatSaint(angels4[timeinfo->tm_mday-1]);
  } 
  if (timeinfo->tm_mon==4){
   return FormatSaint(angels5[timeinfo->tm_mday-1]);
  }    
  if (timeinfo->tm_mon==5){
  return FormatSaint(angels6[timeinfo->tm_mday-1]);
  }
  if (timeinfo->tm_mon==6){  
   return FormatSaint(angels7[timeinfo->tm_mday-1]);
  }  
  if (timeinfo->tm_mon==7){ 
  return FormatSaint(angels8[timeinfo->tm_mday-1]);
  }  
  if (timeinfo->tm_mon==8){ 
  return FormatSaint(angels9[timeinfo->tm_mday-1]);
  }  
  if (timeinfo->tm_mon==9){ 
  return FormatSaint(angels10[timeinfo->tm_mday-1]);
  }  
  if (timeinfo->tm_mon==10){ 
  return FormatSaint(angels11[timeinfo->tm_mday-1]);
  }
  if (timeinfo->tm_mon==11){ 
  return FormatSaint(angels12[timeinfo->tm_mday-1]);
  }   
  return "Glinglin";
}
int oldMinutes;
int oldSecondes;
static bool bFirst=true;
// draws the clock
void drawTime(int top) {
    char time_str[11];
    char saint[80];  
    char *dstAbbrev;  
    time_t now = dstAdjusted.time(&dstAbbrev);
    timeinfo = localtime (&now); 
    int16_t  x1, y1;
    uint16_t w, h;
    String date = ctime(&now);
    int offset=20;   
  if (bFirst)
  {
    display.fillRect(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_WHITE);    
    //date
    display.setFont(&Roboto_Bold_18);   
    date = WDAY_NAMES[timeinfo->tm_wday]+date.substring(7,11) +MONTH_NAMES[timeinfo->tm_mon]+ String(1900 + timeinfo->tm_year);  
    display.getTextBounds((char*)date.c_str(), 0, 0, &x1, &y1, &w, &h);   
     int xcenter=(296-w)/2;  
    display.setCursor(xcenter,top+2);  
    display.println(date);    
    //saint
    display.getTextBounds((char*)GetSaint(timeinfo), 0, 0, &x1, &y1, &w, &h);   
    int xcentre=(296-w)/2;  
    display.setCursor(xcentre, top+100); 
    display.setFont(&Roboto_Bold_24); 
    sprintf(saint,"%s",GetSaint(timeinfo));
    display.println(saint); 
    //display.update();
    display.updateWindow(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, false);   
  }
  //hour and minute
 // if (oldMinutes!=timeinfo->tm_min)
 // {
    display.fillRect(44,42, 208, 49, GxEPD_WHITE);
    display.setCursor(44, top+67);
    display.setFont(&Roboto_Bold_64);    
    sprintf(time_str, "%02d:%02d",timeinfo->tm_hour, timeinfo->tm_min); 
    display.println(time_str);  
    display.setCursor(44+172, top+67); 
    display.setFont(&Roboto_Bold_24);    
    sprintf(time_str, ":%02d", timeinfo->tm_sec); 
    display.println(time_str);  
    oldMinutes=timeinfo->tm_min;
    display.updateWindow(44, 42, 208, 49, true);
  //}
/*  if (oldSecondes!= timeinfo->tm_sec)
  {
//secondes
    display.fillRect(44+172, 60, 50,  30, GxEPD_WHITE);
    display.setCursor(44+172, top+67); 
    display.setFont(&Roboto_Bold_24);    
    sprintf(time_str, ":%02d", timeinfo->tm_sec); 
    display.println(time_str);  
    oldSecondes=timeinfo->tm_sec;
    display.updateWindow(44+172, 60, 50, 30, true);
  }*/
}

void setup()
{
  Serial.begin(115200);  
  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);
  if(!wifiManager.autoConnect("PAPER_CLOCK_V2")) 
  {     
     delay(3000);     
     ESP.reset();
     delay(5000);
  } 
  pinMode(D1, OUTPUT);
  digitalWrite(D1, HIGH);
  display.init();
  digitalWrite(D1, LOW);   
  display.setRotation(3);  
  display.fillScreen(GxEPD_WHITE);
  display.setCursor(60, 70);
  display.setTextColor(GxEPD_BLACK);  
  showFont("Paper Clock V2", &Roboto_Bold_24);    
  display.update();  
  display.updateWindow(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, false);   
  updateData();
  delay(2000);
}
static uint32_t  lastTime = 0; 

void loop()
{  
  if ((millis() - lastTime )>= 300L)
  {
    lastTime = millis();   
    //display.fillRect(0, 10, 280, 128, GxEPD_WHITE);    
    drawTime(22);    
    bFirst=false;    
  }  
  if ((timeinfo->tm_hour==0) && (timeinfo->tm_min==0)&&(timeinfo->tm_sec==0) )
  {
    display.fillScreen(GxEPD_WHITE);
    display.update();
    bFirst=true;
    display.updateWindow(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, true);   
    updateData();  
    delay(1500);  
  }    
}
