//ERÄÄN HOTELLIN VARAUSOHJELMA
// Käyttäjän on mahdollista varata vapaita huoneita itsenäisesti sekä tarkastella varauksensa tietoja. 

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------


#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

struct Rooms						// Esitellään huonetietue, johon varauksen tiedot tallennetaan
{
	int roomNumStruct = 0;				// Huonenumero
	int roomSizeStruct = 0;				// Huonekoko
	int nightsStruct = 0;				// Varatut yöt
	string customerNameStruct = "";		// Varaajan nimi
	int ReservationNumberStruct = 0;	// Varausnumero
	float cost = 0;						// Huoneen hinta
	float finalCost = 0;				// Huoneen hinta alennuksen jälkeen
	bool free = 1;						// Onko huone vapaa, 1=True					
};

Rooms room[260];


// Esitellään funktiot ohjelmalle alla

int randomRoomNum(int genChoice);			// Huonenumerogeneraattori
int randomReservationNumber();				// Varausnumerogeneraattori
int reservationPrinter_name(string search_name);// Tulostetaan structista varauksen sisältö käyttäjälle hakemalla varaajan nimellä
int reservationPrinter(int print_index);	// Tulostetaan structista varauksen sisältö käyttäjälle hakemalla varausnumerolla
void roomSizePrinter(int print_index);		// Muuttaa structin alkion sisällön tekstiksi



int main() 
{ 
	setlocale(LC_ALL, "fi_FI");				// Otettiin ääkköset käyttöön
	SetConsoleOutputCP(1252);				// Mahdollistaa euromerkin (€) tulostamisen

	string menuChoice; // päävalikon syöte, asiakas valitsee mitä halutaan tehdä 

mainMenu:

	cout << "Tervetuloa sähköiseen varauspalveluun!"<< endl 
		
		<<"\n Valitse mitä haluat tehdä" << endl					//Ohjelman päävalikko
		<< "\n 1. Varaa huone"
		<< "\n 2. Tarkastele varausta"
		<< "\n 3. Sulje ohjelma" << endl
		
		<< "\n Syötä numero (1-3): ";

	cin >> menuChoice;
	
	// Pääohjelmassa käytettävät muuttujat 

	// Huoneen varaamisessa käytettävät muuttujat (Päävalikon valinta 1)

	string choice = "";						// Valitaan arvotaanko huone vai valitaanko huonenumero itse 
	string roomSize = "";					// Valittu huonekoko (Single tai Double)
	int roomNumberTemp = 0;					// Käyttäjän syöttämä huonenumero	
	string customerName = "";				// Varauksen tekijän nimi 
	int nights = 0;							// Varattujen öiden määrä
	float totalCost = 0;					// Huoneiden loppusumma (ilman alennusta)
	int discount = 0;						// Alennusgeneraattorin arpoma alennus
	int reservationNum = 0;					// Varausnumero
	string lastChoice;						// Viimeisen valikon valinta (palataanko päävalikkoon vai suljetaanko ohjelma)


	


	while (menuChoice != "3")
	{
		if (menuChoice == "1")
		{
			for (int i = 0; i < 260; i++)					//Tehdään tarkistus onko vapaita huoneita jäljellä
			{
				if (room[i].free)							// Jos huoneita on vapaana, jatketaan huonevaraus-valikkoon
				{
					/*for (int i = 0; i < 260; i++)			// Tarkistetaan varataanko huonetta
					{
						cout << room[i].free;
					}*/
				roomMenu:

					cout << "\n\n----------------------------------------------- " << endl		// Tulostetaan päävalikko
						<< "Hotellissa on tilaa."


						<< "\n\n\nVARAA HUONE" << endl
						<< "-----------------------------------------------" << endl
						<< " Hinnasto:" << endl << endl
						<< "\n Single room (1 hh), 100 " << (char)(128) << " / yö"
						<< "\n Double room (2 hh), 150 " << (char)(128) << " / yö" << endl

						<< "\nValitse haluamasi huone yllä olevista vaihtoehdoista syöttämällä numero 1 tai 2.  \n"
						<< "\n (1 = Single room / 2 = Double room) ";



					cin >> roomSize;						//Käyttäjä syöttää haluamansa huoneen

					if (roomSize == "1")
					 {
						for (int i = 0; i < 130; i++)		// Tarkistetaan onko yhden hengen huoneita vapaana. Jos ei, palataan päävalikkoon
						{
							if (room[i].free == false)
							{
								cout << "-----------------------------------------------" << endl
									<< "\n\nYhden hengen huoneita ei saatavilla. " << endl
									<< "Palataan päävalikkoon." << endl
									<< "-----------------------------------------------" << endl;

								goto mainMenu;
							}

							else						//Jos huoneita vapaana, päästään eteenpäin huonenumeron valintaikkunaan. 
							{

								cout << "\n-----------------------------------------------" << endl
									<< "Yhden hengen huoneita vapaana. " << endl << endl
									<< "\nHaluatko satunnaisen huoneen vai valita huoneen itse?" << endl << endl
									<< "Valitse 1 tai 2 (1 = Satunnainen huone / 2 = Valitsen huoneen itse) ";
								cin >> choice;

								if (choice == "2")
								{
									do
									{
									giveSingleRoom:

										cout << "\n\nAnna huonenumero väliltä 1-130: ";

										cin >> roomNumberTemp;

										if (roomNumberTemp > 130)		//Jos annetaan luku, joka ylittää asetetut rajat, tulostetaan virheilmoitus
										{
											cout << "\n-----------------------------------------------" << endl;
											cout << "\nVirheellinen syöte! " << endl << endl;

											goto giveSingleRoom;		// Palataan huonenumeron syöttämiseen
										}


										if (room[roomNumberTemp - 1].free == 0)		// Tarkastetaan onko huonenumero vapaana: jos arvo false, tulostetaan jälleen virheilmoitus ja ohjataan antamaan uusi huonenumero. 
										{
											cout << "\n\nHuone ei vapaana. Valitse uusi huone.";

											true;

										}


										else
										{
											room[roomNumberTemp - 1].roomNumStruct = roomNumberTemp;		//Tallennetaan huonenumero sekä -koko structiin
											room[roomNumberTemp - 1].roomSizeStruct = 1;
											break;
										}

									} while (true);

								}

								else if (choice == "1")
								{
									int genChoice = 1;

									do
									{
										
										roomNumberTemp = randomRoomNum(genChoice);
									} while (room[roomNumberTemp - 1].free == 0);

									room[roomNumberTemp - 1].roomNumStruct = roomNumberTemp;

									cout << "\n\nHuonenumerosi on " << roomNumberTemp << ".";

								}
							}
							break;
						}
					}

					else if (roomSize == "2")
					{
						 for (int i = 0; i > 131 || i < 260; i++)		//Tarkistetaan onko kahden hengen huoneita vapaana
						 {
							 if (room[i].free == false)
							 {
								 cout << "-----------------------------------------------" << endl
									 << "\n\nKahden hengen huoneita ei saatavilla. " << endl
									 << "Palataan päävalikkoon." << endl
									 << "-----------------------------------------------" << endl;

								 break;

								 goto mainMenu;
							 }
							 else
							 {
								 cout << "-----------------------------------------------" << endl
									 << "Kahden hengen huoneita vapaana. " << endl << endl
									 << "\nHaluatko satunnaisen huoneen vai valita huoneen itse?" << endl
									 << "Valitse 1 tai 2 (1 = Satunnainen huone / 2 = Valitsen huoneen itse) ";
								 cin >> choice;

								 if (choice == "2")
								 {
									 do
									 {
									 giveDoubleRoom:

										 cout << "\n\nAnna huonenumero väliltä 131-260: ";

										 cin >> roomNumberTemp;

										 if (roomNumberTemp < 131)
										 {
											 cout << "\n-----------------------------------------------" << endl;
											 cout << "\nVirheellinen syöte! " << endl << endl;

											 goto giveDoubleRoom;
										 }


										 if (room[roomNumberTemp - 1].free == 0)
										 {
											 cout << "\n\nHuone ei vapaana. Valitse uusi huone.";

											 true;

										 }
										 else
										 {
											 room[roomNumberTemp - 1].roomNumStruct = roomNumberTemp;
											 room[roomNumberTemp - 1].roomSizeStruct = 1;
											 break;
										 }

									 } while (true);

								 }
								 else if (choice == "1")
								 {
									 int genChoice = 2;

									 do
									 {
										 srand((unsigned)time(NULL));
										 roomNumberTemp = 131 + (rand() % 260);			//2 hengen huonenumerogenerointi toimii vakaammin, kun generointi tehdään suoraan eikä funktion kautta


										 //roomNumberTemp = randomRoomNum(genChoice);
									 } while (room[roomNumberTemp - 1].free == 0);

									 room[roomNumberTemp - 1].roomNumStruct = roomNumberTemp;

									 cout << "\n\nHuonenumerosi on " << roomNumberTemp << ".";

								 }
								 break;

							 }

						 }
					}


					else
					{
						cout << "\nVirheellinen syöte."
							<< "\nPalataan päävalikkoon." <<endl;
						cout << "\n-----------------------------------------------" << endl << endl;
						goto mainMenu;
						break;
					}
					break;

				}
				else
				{
					cout << "\nPahoittelut, vapaita huoneita ei ole juuri nyt saatavilla." << endl
						<< "\nPalataan päävalikkoon." << endl;
						cout << "\n-----------------------------------------------" << endl << endl;
						goto mainMenu;
						break;
				}
			}
			int sizechoice = 0;
			if (roomSize == "1")
			{
				sizechoice == 1;
			}
			else if (roomSize == "2")
			{
				sizechoice == 2;
			}



			room[roomNumberTemp - 1].roomSizeStruct == sizechoice;

			cout << "\n\n-----------------------------------------------"
				"\n\nAnna varaajan nimi: ";
			cin.ignore();
			getline(cin, room[roomNumberTemp - 1].customerNameStruct);



			cout << "Anna öiden määrä: ";
			cin >> nights;


			room[roomNumberTemp - 1].nightsStruct = nights;

			room[roomNumberTemp - 1].free = 0;						//Muutetaan huone varatuksi

			
			if (roomNumberTemp <= 130)								//Lasketaan yöpymiskustannukset. Jos huoneen numero on pienempi/yhtäsuuri kuin 130, kerrotaan huoneen hinta öiden määrällä.
			{
				totalCost = nights * 100;

				room[roomNumberTemp - 1].finalCost = totalCost;

				cout << "Yhteensä " << room[roomNumberTemp - 1].finalCost << " " << (char)(128);
			}
			
			else if (roomNumberTemp >= 131)							// Jos huonenumero ylittää 130, kerrotaan öiden määrä kahden hengen huoneen hinnalla
			{
				totalCost = nights * 150;

				room[roomNumberTemp - 1].finalCost = totalCost;

				cout << "Yhteensä " << room[roomNumberTemp - 1].finalCost << " " << (char)(128);
			}

			
			
			//ALENNUSGENERAATTORI

			srand((unsigned)time(NULL));
			discount = 1 + (rand() % 3);			//Arvotaan alennusprosentin määräävä luku (1=0 % / 2=10 % / 3=20 %)

			if (discount != 1)						//Jos kone arpoo ykkösen, ei sitä tulosteta asiakkaalle mielipahan välttämiseksi, koska loppusummasta ei anneta alennusta
			{
				
				if (discount == 2)

				{
					room[roomNumberTemp - 1].finalCost = totalCost * 0.9;
					cout << "\n\n***Olemme päättäneet antaa sinulle varauksesi loppusummasta alennusta 10 %***"
						<< "\nMaksettavaksesi jää " << totalCost * 0.9 << " " << (char)(128) << endl;
				}

				else if (discount == 3)

				{
					room[roomNumberTemp - 1].finalCost = totalCost * 0.8;

					cout << "\n\n***Olemme päättäneet antaa sinulle varauksestasi loppusummasta alennusta 20 %***"
						<< "\nMaksettavaksesi jää " << totalCost * 0.8 << " " << (char)(128) << endl;
				}
			}
			



			reservationNum = randomReservationNumber();						//Kutsutaan aliohjelmaa (arpoo varausnumeron)

			room[roomNumberTemp - 1].ReservationNumberStruct = reservationNum;		//Tallennetaan varausnumero samaan structin samaan indeksiin kuin huonenumero

			cout << "\n-----------------------------------------------" << endl << endl;
			cout << "Varausnumerosi on: " << reservationNum << endl;

			roomSizePrinter(room[roomNumberTemp - 1].roomSizeStruct);
			cout << nights << ":ksi yöksi.";

			cout << "\n\n-----------------------------------------------" << endl << endl
				<< "Palaa päävalikkoon valitsemalla 1" << endl
				<< "Sulje varausohjelma valitsemalla 2" << endl << endl
				<< "Syötä 1 tai 2: ";
			
			cin >> lastChoice;

				if (lastChoice == "1")
				{
					cout<< "\n-----------------------------------------------" << endl << endl;
					goto mainMenu;
				}

				else if (lastChoice == "2")
				{
					goto end; 
				}
				else									

				{
					cout << "\nVirheellinen syöte! Palataan päävalikkoon." << endl
					<< "\n-----------------------------------------------" << endl << endl;

					goto mainMenu;
				}
			
			

		

		}


		else if (menuChoice == "2") // Päävalikon valinta nro 2 ohjaa etsimään varausta joko nimellä tai varausnumerolla
		{

			// Muuttujat varausta tarkastellessa (Päävalikon valinta 2)
			string search;					// Haetaanko varausta nimellä vai varausnumerolla

			cout << "\n-----------------------------------------------" << endl << endl
				<<"Haluatko hakea varausta varausnumerolla vai varaajan nimellä?" << endl << endl
				<< "Syötä 1 (hae varausnumerolla) tai 2 (hae nimellä): ";
			cin >> search;

			if (search == "1")
			{
				int searchReservationNum;

				cout << "\n-----------------------------------------------" << endl << endl
					<< "Anna varausnumerosi: ";
				cin >> searchReservationNum;
				
				reservationPrinter(searchReservationNum);		// Kutsutaan aliohjelmaa
			


				cout << "\n\n-----------------------------------------------" << endl << endl
					<< "Palaa päävalikkoon valitsemalla 1" << endl
					<< "Sulje varausohjelma valitsemalla 2" << endl << endl
					<< "Syötä 1 tai 2: ";

				cin >> lastChoice;

				if (lastChoice == "1") // Ohjaa käyttäjän takaisin päävalikkoon
				{
					cout << "\n-----------------------------------------------" << endl << endl;
					goto mainMenu;
				}

				else if (lastChoice == "2") // Sulkee ohjelman
				{
					goto end;
				}
				else  // Virheilmoitus

				{
					cout << "Virheellinen syöte! Palataan päävalikkoon." << endl
						<< "\n-----------------------------------------------" << endl << endl;

					goto mainMenu;
				}
			}

			else if (search == "2")
			{
				string searchReservationName;

				cout << "\n-----------------------------------------------" << endl << endl
					<< "Anna varaajan nimi: ";
				cin.ignore();
				getline(cin, searchReservationName);
				
				
				reservationPrinter_name(searchReservationName);



				cout << "\n\n-----------------------------------------------" << endl << endl
					<< "Palaa päävalikkoon valitsemalla 1" << endl
					<< "Sulje varausohjelma valitsemalla 2" << endl << endl
					<< "Syötä 1 tai 2: ";

				cin >> lastChoice;

				if (lastChoice == "1")
				{
					cout << "\n-----------------------------------------------" << endl << endl;
					goto mainMenu;
				}

				else if (lastChoice == "2")
				{
					goto end;
				}
				else

				{
					cout << "Virheellinen syöte! Palataan päävalikkoon." << endl
						<< "\n-----------------------------------------------" << endl << endl;

					goto mainMenu;
				}
			}

			else

			{
				cout << "\nVirheellinen syöte! Palataan päävalikkoon." << endl
					<< "\n-----------------------------------------------" << endl << endl;

				goto mainMenu;
			}
		}

		else									// Annetaan virheilmoitus, jos käyttäjä antaa muun luvun kuin 1-3.
				
		{
			cout << "\n\nVirheellinen syöte! Palataan päävalikkoon." 
				<< "\n\n-----------------------------------------------" << endl << endl ;
			
			
			goto mainMenu;
			
			
		}

	}

end:

	cout<< "\n\n-----------------------------------------------" 
		<< "\nKiitos asioinnista sähköisen varauspalvelun kautta!" <<endl
		<< "Sulje ohjelma painamalla mitä tahansa näppäintä. " << endl << endl;

	
	return 0;
}











// ALIOHJELMAT


int randomRoomNum(int genChoice)					//Aliohjelma arpoo satunnaisen huonenumeron 230 huoneesta
{

	int froomNum = 0;								//Alustetaan funktion muuttuja nollaksi

	if (genChoice == 1)
	{
		srand((unsigned)time(NULL));
		froomNum = 1 + (rand() % 130);				//Arvotaan luku 1-130 väliltä
	}

	else if (genChoice == 2)
	{
		srand((unsigned)time(NULL));
		froomNum = 131 + (rand() % 260);				//Arvotaan luku 131-260 väliltä
	}

	return froomNum;								//Palauttaa tuloksen pääohjelmaan
}



int randomReservationNumber()							//Aliohjelma arpoo satunnaisen luvun 10000 ja 99999 väliltä.
{				

	int freservationNum = 0;							//Alustetaan funktion muuttuja nollaksi

	srand((unsigned)time(NULL));
	freservationNum = 10000 + (rand() % 99999);			

	return freservationNum;								//Palauttaa tuloksen pääohjelmaan
}




int reservationPrinter_name(string search_name)		// Etsii varaustiketin varaajan nimellä
{
	
		for (int i = 0; i < 260; i++)
		{
			if (room[i].customerNameStruct == search_name)
			{

				string roomType;

				if (room[i].roomSizeStruct == 0)
				{
					roomType = "Single room";
				}

				else if (room[i].roomSizeStruct == 1)
				{
					roomType = "Double room";
				}

				else
				{
					roomType = "VIRHE";
				}

				cout << "\n\n-----------------------------------------------" << endl;
				cout << "\nVARAUKSESI" << endl << endl <<endl;
				cout << "\nVARAUSNUMERO: " << room[i].ReservationNumberStruct << endl;
				cout << "\nVARAAJA: " << room[i].customerNameStruct;
				cout << "\nHUONETYYPPI: " << roomType;
				cout << "\nHUONENUMERO: " << room[i].roomNumStruct;
				cout << "\nVARATUT YÖT: " << room[i].nightsStruct << " yötä";
				cout << "\nLOPPUSUMMA: " << room[i].finalCost << " " << (char)(128);
				//cout << "\n\n-----------------------------------------------";

				return 0;
				
				
				

			}
			
		}

		cout << "Varausta ei löytynyt." << endl;
		
		return 0;



}


int reservationPrinter(int print_index) // Etsii varaustiketin varausnumerolla
{

	for (int i = 0; i < 260; i++)
	{
		if (room[i].ReservationNumberStruct == print_index)
		{

			string roomType;

			if (room[i].roomSizeStruct == 0)
			{
				roomType = "Single room";
			}

			else if (room[i].roomSizeStruct == 1)
			{
				roomType = "Double room";
			}

			else
			{
				roomType = "VIRHE";
			}

			cout << "\n\n-----------------------------------------------" << endl;
			cout << "\nVARAUSNUMERO: " << room[i].ReservationNumberStruct << endl;
			cout << "\nVARAAJA: " << room[i].customerNameStruct;
			cout << "\nHUONETYYPPI: " << roomType;
			cout << "\nHUONENUMERO: " << room[i].roomNumStruct;
			cout << "\nVARATUT YÖT: " << room[i].nightsStruct << " yötä";
			cout << "\nLOPPUSUMMA: " << room[i].finalCost << " " << (char)(128);
			//cout << "\n\n-----------------------------------------------";

			return 0;
			

		}
		
	}
	
		cout << "Varausta ei löytynyt." << endl;

		return 0;
		
	
}


	
void roomSizePrinter(int print_index)				//Muutetaan huonetyyppi sanaksi, jotta pääohjelman ilmoitus varauksen onnistumisesta on sujuvampaa kieltä. 
{
	string froomSize;

	if (print_index == 0)
	{
		froomSize = "yhden";
	}

	else if (print_index == 1)
	{
		froomSize = "kahden";
	}

	else
	{
		froomSize = "VIRHE";
	}

	cout << "\nOlet nyt varannut " << froomSize << " hengen huoneen onnistuneesti ";

}

