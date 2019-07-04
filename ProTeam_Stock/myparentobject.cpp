#include "MyParentObject.h"

#include <QStringList>

MyParentObject::MyParentObject()
{
    thisPath = QDir::toNativeSeparators(QApplication::applicationDirPath());
    settingsFilePath = thisPath +"/settings.ini" ;
    _mySettings = new QSettings(settingsFilePath, QSettings::IniFormat);

}

MyParentObject::~MyParentObject()
{
      delete _mySettings;
}

QString MyParentObject::convertWhidaToLetter(QString whida, int position)
{
    QStringList tableTwoNumber ;
    {
    tableTwoNumber << "" ;
    tableTwoNumber << "	un Dinars 	";
    tableTwoNumber << "	deux Dinars 	";
    tableTwoNumber << "	trois Dinars 	";
    tableTwoNumber << "	quatre Dinars 	";
    tableTwoNumber << "	cinq Dinars 	";
    tableTwoNumber << "	six Dinars 	";
    tableTwoNumber << "	sept Dinars 	";
    tableTwoNumber << "	huit Dinars 	";
    tableTwoNumber << "	neuf Dinars 	";
    tableTwoNumber << "	dix Dinars 	";
    tableTwoNumber << "	onze Dinars 	";
    tableTwoNumber << "	douze Dinars 	";
    tableTwoNumber << "	treize Dinars 	";
    tableTwoNumber << "	quatorze Dinars 	";
    tableTwoNumber << "	quinze Dinars 	";
    tableTwoNumber << "	seize Dinars 	";
    tableTwoNumber << "	dix sept Dinars 	";
    tableTwoNumber << "	dix huit Dinars 	";
    tableTwoNumber << "	dix neuf Dinars 	";
    tableTwoNumber << "	vingt Dinars 	";
    tableTwoNumber << "	vingt et un Dinars 	";
    tableTwoNumber << "	vingt deux Dinars 	";
    tableTwoNumber << "	vingt trois Dinars 	";
    tableTwoNumber << "	vingt quatre Dinars 	";
    tableTwoNumber << "	vingt cinq Dinars 	";
    tableTwoNumber << "	vingt six Dinars 	";
    tableTwoNumber << "	vingt sept Dinars 	";
    tableTwoNumber << "	vingt huit Dinars 	";
    tableTwoNumber << "	vingt neuf Dinars 	";
    tableTwoNumber << "	trente Dinars 	";
    tableTwoNumber << "	trente et un Dinars 	";
    tableTwoNumber << "	trente deux Dinars 	";
    tableTwoNumber << "	trente trois Dinars 	";
    tableTwoNumber << "	trente quatre Dinars 	";
    tableTwoNumber << "	trente cinq Dinars 	";
    tableTwoNumber << "	trente six Dinars 	";
    tableTwoNumber << "	trente sept Dinars 	";
    tableTwoNumber << "	trente huit Dinars 	";
    tableTwoNumber << "	trente neuf Dinars 	";
    tableTwoNumber << "	quarante Dinars 	";
    tableTwoNumber << "	quarante et un Dinars 	";
    tableTwoNumber << "	quarante deux Dinars 	";
    tableTwoNumber << "	quarante trois Dinars 	";
    tableTwoNumber << "	quarante quatre Dinars 	";
    tableTwoNumber << "	quarante cinq Dinars 	";
    tableTwoNumber << "	quarante six Dinars 	";
    tableTwoNumber << "	quarante sept Dinars 	";
    tableTwoNumber << "	quarante huit Dinars 	";
    tableTwoNumber << "	quarante neuf Dinars 	";
    tableTwoNumber << "	cinquante Dinars 	";
    tableTwoNumber << "	cinquante et un Dinars 	";
    tableTwoNumber << "	cinquante deux Dinars 	";
    tableTwoNumber << "	cinquante trois Dinars 	";
    tableTwoNumber << "	cinquante quatre Dinars 	";
    tableTwoNumber << "	cinquante cinq Dinars 	";
    tableTwoNumber << "	cinquante six Dinars 	";
    tableTwoNumber << "	cinquante sept Dinars 	";
    tableTwoNumber << "	cinquante huit Dinars 	";
    tableTwoNumber << "	cinquante neuf Dinars 	";
    tableTwoNumber << "	soixante Dinars 	";
    tableTwoNumber << "	soixante et un Dinars 	";
    tableTwoNumber << "	soixante deux Dinars 	";
    tableTwoNumber << "	soixante trois Dinars 	";
    tableTwoNumber << "	soixante quatre Dinars 	";
    tableTwoNumber << "	soixante cinq Dinars 	";
    tableTwoNumber << "	soixante six Dinars 	";
    tableTwoNumber << "	soixante sept Dinars 	";
    tableTwoNumber << "	soixante huit Dinars 	";
    tableTwoNumber << "	soixante neuf Dinars 	";
    tableTwoNumber << "	soixante dix Dinars 	";
    tableTwoNumber << "	soixante et onze Dinars 	";
    tableTwoNumber << "	soixante douze Dinars 	";
    tableTwoNumber << "	soixante treize Dinars 	";
    tableTwoNumber << "	soixante quatorze Dinars 	";
    tableTwoNumber << "	soixante quinze Dinars 	";
    tableTwoNumber << "	soixante seize Dinars 	";
    tableTwoNumber << "	soixante dix sept Dinars 	";
    tableTwoNumber << "	soixante dix huit Dinars 	";
    tableTwoNumber << "	soixante dix neuf Dinars 	";
    tableTwoNumber << "	quatre-vingts Dinars 	";
    tableTwoNumber << "	quatre-vingt un Dinars 	";
    tableTwoNumber << "	quatre-vingt deux Dinars 	";
    tableTwoNumber << "	quatre-vingt trois Dinars 	";
    tableTwoNumber << "	quatre-vingt quatre Dinars 	";
    tableTwoNumber << "	quatre-vingt cinq Dinars 	";
    tableTwoNumber << "	quatre-vingt six Dinars 	";
    tableTwoNumber << "	quatre-vingt sept Dinars 	";
    tableTwoNumber << "	quatre-vingt huit Dinars 	";
    tableTwoNumber << "	quatre-vingt neuf Dinars 	";
    tableTwoNumber << "	quatre-vingt dix Dinars 	";
    tableTwoNumber << "	quatre-vingt onze Dinars 	";
    tableTwoNumber << "	quatre-vingt douze Dinars 	";
    tableTwoNumber << "	quatre-vingt treize Dinars 	";
    tableTwoNumber << "	quatre-vingt quatorze Dinars 	";
    tableTwoNumber << "	quatre-vingt quinze Dinars 	";
    tableTwoNumber << "	quatre-vingt seize Dinars 	";
    tableTwoNumber << "	quatre-vingt dix sept Dinars 	";
    tableTwoNumber << "	quatre-vingt dix huit Dinars 	";
    tableTwoNumber << "	quatre-vingt dix neuf Dinars 	";
    }

    QStringList numberletter10 ;
    numberletter10 << "" <<"" << "deux" << "trois" << "quatre"<< "cinq"<< "six";
    numberletter10 << "sept"<< "huit" << "neuf" ;
    //qDebug() << numberletter10;
    QStringList wihdat ;
    wihdat << "" << " Mille " << " Million " << " Milliard " ;
    QString returnString ;
    if( whida.length() == 3 && whida != "000" )
    {

        QCharRef a = whida[0] ;
        QString x;
        x += a ;
        QCharRef b = whida[1] ;
        QCharRef c = whida[2] ;
        QString y ;
        y += b ;
        y += c ;
        //qDebug() << numberletter10 << y;
        //returnString += numberletter10[ y.toInt() ] + " cents " + tableTwoNumber[y.toInt()] ;
        if( y.toInt() == 0  && x.toInt() == 1)
        {
            returnString += " cent " ;
            returnString +=  tableTwoNumber[y.toInt()];
        }
        else
        {
            if ( x.toInt() == 0)
            {
                returnString +=  tableTwoNumber[y.toInt()];
            }
            else
            {
                returnString += numberletter10[ x.toInt() ] + " cents ";
                returnString +=  tableTwoNumber[y.toInt()];
            }

        }
    }
    else
    {
        if( whida.length() == 1 )
        {   if ( position > 1 )
            {   if( whida.toInt() == 1 )
                {
                    returnString += numberletter10[whida.toInt()] + " un " + wihdat[position] ;
                    return returnString ;
                }
            }
            returnString += numberletter10[whida.toInt()] + wihdat[position] ;
            return returnString ;
        }
        returnString += tableTwoNumber[whida.toInt()] ;
    }
    returnString +=  wihdat[position] ;
    return returnString ;
}
QString MyParentObject::spellLetter(QString number)
{
    qDebug() << "QString MyParentObject::spellLetter(QString number): " << number;
    if ( number.isEmpty())
    {
        return "";
    }

    QStringList ThreeNumber ;
    QString tmp01 ;
    int kisma = number.length() / 3 ;
    int baki = number.length() % 3 ;
    int vergulCount=0;
    vergulCount++ ; vergulCount-- ;

    if( baki == 0 ) vergulCount = kisma -1 ;
    else vergulCount = kisma ;
    int j = 0 ;
    for ( int i = number.length() - 1 ; i >= 0 ; i-- , j++ )
    {
        if ( j == 3 )
        {
            j = 0 ;
            tmp01 +=',';
        }
        tmp01 += number[i];

    }

    number.clear();
    for ( int i = tmp01.length() - 1 ; i >= 0 ; i-- , j++ )
    {
        number += tmp01[i];
    }

    QStringList wihdatCount = number.split(",") ;
    j = 0 ;
    QStringList tmp02 ;
    for ( int i = wihdatCount.length() -1 ; i >= 0 ; i-- , j++ )
    {
        tmp02 << convertWhidaToLetter(wihdatCount[i], j) ;
    }

    QString tmp03 ;
    for ( int i = tmp02.length() -1  ; i >= 0 ; i-- )
    {
        QString tmp04 = tmp02[i];
        tmp03 +=  tmp04 ;
    }
    return tmp03 ;
}

bool MyParentObject::msgQuestion(QString title ,QString body)
{
    qDebug() << "title: "+ title << "\nboady: "+ body ;
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(body);
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes){
      return true ;
    }

    return false ;
}
void MyParentObject::msgCritical(QString title ,QString body)
{
    qDebug() << "title: "+ title << "\nboady: "+ body ;
    QMessageBox::critical(0,title,body);
}
void MyParentObject::msgInformation(QString title ,QString body)
{
    qDebug() << "title: "+ title << "\nboady: "+ body ;
    QMessageBox::information(0,title,body);
}
void MyParentObject::msgWarning(QString title ,QString body)
{
    qDebug() << "title: "+ title << "\nboady: "+ body ;
    QMessageBox::warning(0,title,body);
}

void MyParentObject::setSettings(QString key, QVariant data)
{
    _mySettings->setValue(key, data);
}

QVariant MyParentObject::getSettings(QString key)
{
    return _mySettings->value(key) ;
}

void MyParentObject::chiffreEnLettre(unsigned int chiffre, char *lettre){
    unsigned int centaine, dizaine, unite, reste, y;
    bool dix = false;
    strcpy(lettre, "");
    reste = chiffre;
    for(int i=1000000000; i>=1; i/=1000)
    {
        y = reste/i;
        if(y!=0)
        {
            centaine = y/100;
            dizaine  = (y - centaine*100)/10;
            unite = y-(centaine*100)-(dizaine*10);
            switch(centaine)
            {
            case 0:
                break;
            case 1:
                strcat(lettre,"cent ");
                break;
            case 2:
                if((dizaine == 0)&&(unite == 0)) strcat(lettre,"deux cents ");
                else strcat(lettre,"deux cent ");
                break;
            case 3:
                if((dizaine == 0)&&(unite == 0)) strcat(lettre,"trois cents ");
                else strcat(lettre,"trois cent ");
                break;
            case 4:
                if((dizaine == 0)&&(unite == 0)) strcat(lettre,"quatre cents ");
                else strcat(lettre,"quatre cent ");
                break;
            case 5:
                if((dizaine == 0)&&(unite == 0)) strcat(lettre,"cinq cents ");
                else strcat(lettre,"cinq cent ");
                break;
            case 6:
                if((dizaine == 0)&&(unite == 0)) strcat(lettre,"six cents ");
                else strcat(lettre,"six cent ");
                break;
            case 7:
                if((dizaine == 0)&&(unite == 0)) strcat(lettre,"sept cents ");
                else strcat(lettre,"sept cent ");
                break;
            case 8:
                if((dizaine == 0)&&(unite == 0)) strcat(lettre,"huit cents ");
                else strcat(lettre,"huit cent ");
                break;
            case 9:
                if((dizaine == 0)&&(unite == 0)) strcat(lettre,"neuf cents ");
                else strcat(lettre,"neuf cent ");
            }
            switch(dizaine)
            {
            case 0:
                break;
            case 1:
                dix = true;
                break;
            case 2:
                strcat(lettre,"vingt ");
                break;
            case 3:
                strcat(lettre,"trente ");
                break;
            case 4:
                strcat(lettre,"quarante ");
                break;
            case 5:
                strcat(lettre,"cinquante ");
                break;
            case 6:
                strcat(lettre,"soixante ");
                break;
            case 7:
                dix = true;
                strcat(lettre,"soixante ");
                break;
            case 8:
                strcat(lettre,"quatre-vingt ");
                break;
            case 9:
                dix = true;
                strcat(lettre,"quatre-vingt ");
            } // endSwitch(dizaine)

            switch(unite)
            {
            case 0:
                if(dix) strcat(lettre,"dix ");
                break;
            case 1:
                if(dix) strcat(lettre,"onze ");
                else    strcat(lettre,"un ");
                break;
            case 2:
                if(dix) strcat(lettre,"douze ");
                else    strcat(lettre,"deux ");
                break;
            case 3:
                if(dix) strcat(lettre,"treize ");
                else    strcat(lettre,"trois ");
                break;
            case 4:
                if(dix) strcat(lettre,"quatorze ");
                else    strcat(lettre,"quatre ");
                break;
            case 5:
                if(dix) strcat(lettre,"quinze ");
                else    strcat(lettre,"cinq ");
                break;
            case 6:
                if(dix) strcat(lettre,"seize ");
                else    strcat(lettre,"six ");
                break;
            case 7:
                if(dix) strcat(lettre,"dix-sept ");
                else    strcat(lettre,"sept ");
                break;
            case 8:
                if(dix) strcat(lettre,"dix-huit ");
                else    strcat(lettre,"huit ");
                break;
            case 9:
                if(dix) strcat(lettre,"dix-neuf ");
                else    strcat(lettre,"neuf ");
            } // endSwitch(unite)

            switch (i)
            {
            case 1000000000:
                if(y>1) strcat(lettre,"milliards ");
                else strcat(lettre,"milliard ");
                break;
            case 1000000:
                if(y>1) strcat(lettre,"millions ");
                else strcat(lettre,"million ");
                break;
            case 1000:
                strcat(lettre,"mille ");
            }
        }
        reste -= y*i;
        dix = false;
    }
    if(strlen(lettre)==0) strcpy(lettre,"zero");
}
QString MyParentObject::result(int number){
    char c[256];

    chiffreEnLettre(number,c);
    return QString(c);
}
QString MyParentObject::addcommat(unsigned long long n)
{
    std::string s;
    int cnt = 0;
    do
    {
        s.insert(0, 1, char('0' + n % 10));
        n /= 10;
        if (++cnt == 3 && n)
        {
            s.insert(0, 1, ',');
            cnt = 0;
        }
    } while (n);
    return QString::fromStdString(s);
}

