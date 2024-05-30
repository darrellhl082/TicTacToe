#include <iostream> //library input cin cout
#include <conio.h>// getch()
#include <string> // string
#include <vector> // vector
#include <limits> //limit
#include <windows.h> //Sleep
using namespace std;

//Prototipe deklarasi fungsi
void isiPapan(string (*board)[3][3], int x, int y, char player, bool *status); //Isi papan
void cetakPapan(string board[3][3]);// untuk deklarasi fungsi cetak papan
bool cekPemenang(string board[3][3], char player, char *winner); // untuk deklarasi fungsi cek pemenang

//deklarasi struct
struct dataPermainan{ // nama struct 
    string board[3][3] = {{ "[ ]", "[ ]", "[ ]"}, {"[ ]", "[ ]", "[ ]"}, {"[ ]", "[ ]", "[ ]"}}; // isi dalam struct yang nantinya akan disimpan kedalam dataPermainan
    string mode; // isi dalam struct untuk menyimpan mode yang digunakan pada dataPermainan 
    string namaX, namaO, pemenang; // isi dalam struct untuk nama player dan pemenang yang disimpan pada dataPermainan
    char winner = ' '; // isi dalam struct yang berisikan variabel winner dengan nilai ' ' atau kosong
};

//deklarasi vector
vector <dataPermainan> vectorData; // deklarasi vector yang bernama vector data yang menyimpan dataPermainan

int main()
{   
    //deklatasi variabel yang digunakan
    bool gamend = false, status = true; // deklarasi variabel keadaan awal gamend & status
    int jalan, pilMenu; // deklarasi variabel jalan & pilihan menu
    char player, winner = ' '; // deklarasi variabel player & winner 
    int x, y; // deklarasi variabel x dan y
    
    dataPermainan templateData; // mendeklarasikan struct bernama templateData
    //looping program
    while(true){
        system("cls"); // untuk membersihkan layar
        cout << "==============[ TIC TAC TOE ]=================" << endl;
        cout << "1. Player vs Player" << endl;
        cout << "2. Player vs Computer" << endl;
        cout << "3. Riwayat Permainan" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih: "; 
        //prevent error: invalid input
        while (!(cin >> pilMenu)) { // ketika pilihan menu bernilai false 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // untuk memastikan limit angka yang dapat di input
            cout << "Input tidak valid, masukkan angka: ";
        }
        
        if (pilMenu == 1){ // kondisi pilihan 1 bernilai true
            jalan = 0; // nilai variabel jalan = 0
            winner = ' '; // nilai variabel winner 
            system("cls");
            cout << "==============[ TIC TAC TOE ]=================" << endl;
            cout << "Mode Player vs Player" << endl;
            cout << "Nama Player X: "; 
            cin.ignore();
            getline(cin, templateData.namaX);// memasukan nama player X kedalam struct templateData
            cout << "Nama Player O: "; 
            getline(cin, templateData.namaO);// memasukan nama player O kedalam struct templateData
            //Looping alur permainan
            while (!gamend){ // ketika gamend bernilai false maka permainan akan berjalan
                system("cls");
                cout << "==============[ TIC TAC TOE ]=================" << endl;
                cetakPapan(templateData.board); // memanggil funsi cetakPapan untuk menampilkan papan permainan
                if (jalan > 8){ // ketika nilai jalan permainan sudah dilakukan > 8 kali maka permainan akan selesai
                    break;
                }
                else if (jalan % 2 == 0){ // jika kondisi jalan permaianan masih 0 atau genap maka player X bermain
                    player = 'X';   
                } else { // jika kondisi jalan permaianan bernilai ganjil maka player O bermain
                    player = 'O';
                }
                cout << endl;
                cout << "Player " << player << " Jalan" << endl;
                cout << "Masukan koordinat (Baris,Kolom)= "; 
                while (!(cin >> x && x > 0 && x < 4)) { // ketika angka yang dimasukan tidak valid maka akan terjadi pengulangan sehingga pemain diminta memasukan koordinat yang benar
                    
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout << "Input tidak valid" << endl; 
                    cout << "Masukan koordinat (Baris,Kolom)= "; 
                }
               
                while (!(cin >> y && y > 0 && y < 4)) { // ketika angka yang dimasukan tidak valid maka akan terjadi pengulangan sehingga pemain diminta memasukan koordinat yang benar
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Input tidak valid" << endl;
                    cout << "Masukan koordinat (Baris,Kolom)= ";
                } 
                isiPapan(&(templateData.board), x, y, player, &status); // memanggil fungsi isiPapan yang menggunakan alamat templatedata.board

                if (status == true){ // kondisi dimana status bernilai true, maka permainan akan berjalan terus
                    jalan++;
                } else { // namun jika kondisi status bernilai false, makan player akan diminta untuk mengisi koordinat lain yang belum terisi
                    cout << "Board Sudah terisi" << endl;
                    Sleep(500); // untuk mendelay permainan
                    status = true; // mengubah nilai status yang tadinya false menjadi true
                }
                gamend = cekPemenang(templateData.board, player, &winner); // memberikan nilai pada gamend dan memanggil fungsi cekPemenang
            }
            
            //Mengurus pemenang
            Sleep(1000); // delay program 
            if(winner == ' '){ // kondisi ketika winner bernilai ' ' atau kosong, maka ditampilkan "tidak ada pemenang"
                cout << "Tidak ada pemenang" << endl;
                templateData.pemenang = "Tidak ada pemenang"; // menyimpan hasil permainan ke struct templateData.pemenang
            } else { 
                if(winner == 'X'){ // kondisi ketika winner bernilai X 
                    templateData.pemenang = templateData.namaX; // menyimpan hasil permainan ke struct templateData.pemenang
                } else {  // kondisi ketika winner bernilai O
                    templateData.pemenang = templateData.namaO; // menyimpan hasil permainan ke struct templateData.pemenang
                }
                cout << "Pemenang adalah: " << templateData.pemenang << " (" << winner << ")" << endl; // memampilkan pemenang permainan
                cout << "Tekan untuk keluar" << endl;
            }
            getch(); // pause
            gamend = false; // mereset nilai

            //Store data ke vector riwayat
            templateData.winner = winner; // menyimpan nilai winner ke struct templateData.winner
            templateData.mode = "Player VS Player"; // menyimpan nilai mode permainan ke struct templateData.mode
            vectorData.push_back(templateData); // memasukan data permainan dari struct templateData ke dalam vectorData

            //Mengembalikan isi board menjadi seperti awal atau dikosongkan
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3;j++){
                    templateData.board[i][j] = "[ ]";
                }
            }
        
            system("cls");
        } else if (pilMenu == 2){
            jalan = 0;
            winner = ' ';
            srand(time(0)); // mengacak nilai angka
            system("cls");
            cout << "==============[ TIC TAC TOE ]=================" << endl;
            cout << "Mode Player vs Computer" << endl;
            cout << "Nama Player X: ";  
            cin.ignore();
            getline(cin, templateData.namaX); 
            cout << "Nama Plater O: Computer"; 
            templateData.namaO = "Computer";
            //looping permainan
            while (!gamend){
                system("cls");
                cout << "==============[ TIC TAC TOE ]=================" << endl;
                cetakPapan(templateData.board);
                if (jalan > 8){
                    break;
                }
                else if (jalan % 2 == 0){
                    player = 'X';   
                } else {
                    player = 'O';
                    Sleep(1000);
                }
                cout << endl;
                cout << "Player " << player << " Jalan" << endl;
               
                // kondisi ketika pemain O atau computer bermain
                if (player == 'O'){  
                    x = rand()% 3+1; // mengacak angka dari 1-3 menggunakan bilangan acak/random
                    y = rand()% 3+1; // mengacak angka dari 1-3 menggunakan bilangan acak/random
                } else if (player == 'X') {
                    cout << "Masukan koordinat (Baris,Kolom)= "; 
                    while (!(cin >> x && x > 0 && x < 4)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Input tidak valid" << endl;
                        cout << "Masukan koordinat (Baris,Kolom)= "; 
                    }
                    while (!(cin >> y && y > 0 && y < 4)) { 
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Input tidak valid" << endl;
                        cout << "Masukan koordinat (Baris,Kolom)= "; 
                    }
                }

                isiPapan(&(templateData.board), x, y, player, &status);
                
                if (status == true){
                    jalan++;
                } else {
                    cout << "Board Sudah terisi" << endl;
                    Sleep(500);
                    status = true;
                }
                gamend = cekPemenang(templateData.board, player, &winner);
            }
            
            Sleep(1000);
            //mengurus pemenang
            if(winner == ' '){
                cout << "Tidak ada pemenang" << endl;
                templateData.pemenang = "Tidak ada pemenang";
            } else {
                if(winner == 'X'){
                    templateData.pemenang = templateData.namaX;
                } else {    
                    templateData.pemenang = templateData.namaO;
                }
                cout << "Pemenang adalah: " << templateData.pemenang << " (" << winner << ")" << endl;
                cout << "Tekan untuk keluar" << endl;
            }
            getch();

            gamend = false;

            //store struct template wadah ke vector riwayat
            templateData.winner = winner;
            templateData.mode = "Player VS Computer";
            vectorData.push_back(templateData);

            //mengosongkan atau membersihkan papan
            for (int i = 0; i < 3; i++){
                for (int j = 0; j < 3;j++){
                    templateData.board[i][j] = "[ ]";
                }
            }
        } else if (pilMenu == 3){ // ketika memilih pilihan 3
            system("cls");
            cout << "=======Riwayat Permainan========" << endl << endl;
            
            //Looping vector riwayat
            for(int i = 0; i < vectorData.size(); i++){ // melooping histori permainan ke-
                cout << i+1 << ".\tPemenang: " << vectorData[i].pemenang << " (" << vectorData[i].winner << ")" << endl; // menampilkan isi dari vector 
                cout << "  \tMode: " << vectorData[i].mode << endl; // menampilkan isi dari vector 
                cout << "  \t" << vectorData[i].namaX << " (X)" << endl; // menampilkan isi dari vector 
                cout << "  \t" << vectorData[i].namaO << " (O)" << endl; // menampilkan isi dari vector 
                cout << endl;
                for(int j = 0; j < 3;j++){
                    cout << "  \t";
                    for (int k = 0; k < 3;k++){
                        cout << vectorData[i].board[j][k]; // menampilkan histori board permainan 
                    }
                    cout << endl;
                }
                cout << endl;
            }
            cout << "\nTekan untuk keluar" << endl;
            getch();
        } else if (pilMenu == 4){
            cout << "\nTerima Kasih" << endl;
            break;
        } else {
            cout << "\nTidak Valid" << endl;
        }
    }   
    
    getch();
    return 0;
}

//definisi fungsi prosedur isi papan
// kondisi *board menerima alamat dari &board yang kemudian nilainya akan dimodifikasi di dalam fungsi
void isiPapan(string (*board)[3][3],int x, int y, char player, bool *status){ // menggunakan parameter variabel *board, x, y, player, *player
    if((*board)[x-1][y-1] == "[ ]") //mengecek apakah sel yang dituju oleh player kosong, jika kosong maka status true, jika terisi maka status false
    {
        if (player == 'X'){
            (*board)[x-1][y-1] = "[X]";
        } else if (player == 'O'){
            (*board)[x-1][y-1] = "[O]";
        }
    } else {
        *status = false; // *status menerima alamat data dari &status yang nantinya akan mengubah nilai alamat data *status menjadi false
        //nilai dari alamat pointer status akan diubah menjadi false
    }
}

//definisi fungsi prosedur cetakpapan
void cetakPapan(string board[3][3]){
    for(int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
           cout << board[i][j];
        }
        cout << endl;
    }
}

//definisi fungsi cekpemenang
bool cekPemenang(string board[3][3], char player, char *winner){
    if(player == 'X'){ // kondisi ketika player bernilai X, jika true maka akan lanjut ke kondisi atau if berikutnya
        // pengecekan satu persatu player X secara horizontal, vertikal, dan diagonal
        if (board[0][0] == "[X]" &&  board[0][1] == "[X]" && board[0][2] == "[X]"){ 
            *winner = player; // mengubah nilai dari pointer winner menjadi player X, jika sejajar
            return true; // harus ada karna tipe data yang gunakan bukan void
        } else if (board[1][0] == "[X]" &&  board[1][1] == "[X]" && board[1][2] == "[X]"){
            *winner = player;
            return true;
        } else if (board[2][0] == "[X]" &&  board[2][1] == "[X]" && board[2][2] == "[X]"){
            *winner = player;
            return true;
        } else if (board[0][0] == "[X]" &&  board[1][0] == "[X]" && board[2][0] == "[X]"){
            *winner = player;
            return true;
        } else if (board[0][1] == "[X]" &&  board[1][1] == "[X]" && board[2][1] == "[X]"){
            *winner = player;
            return true;
        } else if (board[0][2] == "[X]" &&  board[1][2] == "[X]" && board[2][2] == "[X]"){
            *winner = player;
            return true;
        } else if (board[0][0] == "[X]" &&  board[1][1] == "[X]" && board[2][2] == "[X]"){
            *winner = player;
            return true;
        } else if (board[0][2] == "[X]" &&  board[1][1] == "[X]" && board[2][0] == "[X]"){
            *winner = player;
            return true;
        }           
        // jika dari kondisi pertama tidak true maka akan langsung masuk ke keadaan ketika player bernilai O
    } else {
        // pengecekan satu persatu player X secara horizontal, vertikal, dan diagonal
         if (board[0][0] == "[O]" &&  board[0][1] == "[O]" && board[0][2] == "[O]"){
            *winner = player; // mengubah nilai dari pointer winner menjadi player X, jika sejajar
            return true;
        } else if (board[1][0] == "[O]" &&  board[1][1] == "[O]" && board[1][2] == "[O]"){
            *winner = player;
            return true;
        } else if (board[2][0] == "[O]" &&  board[2][1] == "[O]" && board[2][2] == "[O]"){
            *winner = player;
            return true;
        } else if (board[0][0] == "[O]" &&  board[1][0] == "[O]" && board[2][0] == "[O]"){
            *winner = player;
            return true;
        } else if (board[0][1] == "[O]" &&  board[1][1] == "[O]" && board[2][1] == "[O]"){
            *winner = player;
            return true;
        } else if (board[0][2] == "[O]" &&  board[1][2] == "[O]" && board[2][2] == "[O]"){
            *winner = player;
            return true;
        } else if (board[0][0] == "[O]" &&  board[1][1] == "[O]" && board[2][2] == "[O]"){
            *winner = player;
            return true;
        } else if (board[0][2] == "[O]" &&  board[1][1] == "[O]" && board[2][0] == "[O]"){
            *winner = player;
            return true;
        }           
    }
    return false; // harus ada karna tipe data yang gunakan bukan void

}