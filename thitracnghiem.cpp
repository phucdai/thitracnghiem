#include <iostream>
#include <string>
#define MAXLIST 1000
using namespace std;
string username;
string password;

// DANH SACH MON HOC ================================================
struct monhoc {
	string mamh;
	string tenmh;
};
typedef struct monhoc Monhoc;

struct danhsachmonhoc {
	int n;
	Monhoc nodes[MAXLIST];
};
typedef struct danhsachmonhoc Dsmh;

// kiem tra danh sach co rong khong
int Empty(Dsmh &mh) {
	return mh.n==0 ;
}

// kiem tra danh sach full chua
int Full(Dsmh mh) {
	return mh.n==MAXLIST;
}

// them mon hoc vao vi tri i
int Insert_Monhoc(Dsmh &mh, int i, Monhoc info) {
	int j;
	if (i < 0 || i > mh.n || Full(mh)) return 0;
	for (int j=mh.n-1; j>=i; j--) {
		mh.nodes[j+1] = mh.nodes[j];
	}
	mh.nodes[i] = info;
	mh.n += 1;
	
	return 1;
}

int Modify_Monhoc(Dsmh &mh, int i, Monhoc info) {
	int j;
	if (i < 0 || i > mh.n) return 0;
	mh.nodes[i] = info;
	
	return 1;
}

int Delete_Monhoc(Dsmh &mh, int i) {
	int j;
	if (i < 0 || i > mh.n || mh.n == 0) return 0;
	for (int j=i+1; j<mh.n; j++) {
		mh.nodes[j-1] = mh.nodes[j];
	}
	mh.n -= 1;
	
	return 1;
}

void ShowDanhSachMonHoc(Dsmh mh) {
	for (int i=0; i<mh.n; i++) {
		cout << "\nma mon hoc: "; cout << mh.nodes[i].mamh;
		cout << "\nten mon hoc: "; cout << mh.nodes[i].tenmh;
	}
}

// </ DANH SACH MON HOC ===============================================


//  DANH SACH SV ===================================================

struct sinhvien {
	string masv;
	string ho;
	string ten;
	string phai;
	string password;
};
typedef struct sinhvien Sinhvien;

struct nodeSv {
	Sinhvien *data;
	struct nodeSv *pNext;
};
typedef struct nodeSv NodeSv;

struct listSv {
	NodeSv *pHead;
	NodeSv *pTail;
};
typedef struct listSv ListSv;

void KhoiTaoListSv(ListSv &l) {
	l.pHead = l.pTail = NULL;
}

void Input_Sinhvien(Sinhvien *sv, string msv) {
	sv->masv = msv;
	cin.ignore();
	cout << "\nNhap ho: "; getline(cin,sv->ho);
	cout << "\nNhap ten: "; getline(cin,sv->ten);
	cout << "\nNhap phai (nam/nu): "; getline(cin,sv->phai);
	cout << "\nNhap password: "; getline(cin,sv->password);
}

NodeSv *KhoiTaoNodeSv(string msv) {
	Sinhvien *sv = new Sinhvien;
	Input_Sinhvien(sv, msv);
	NodeSv *p = new NodeSv;
	if (p == NULL) {
		cout << "\nFull ram khong the them duoc";
		return 0;
	}
	p->data = sv;
	p->pNext = NULL;
	return p;
}

void ThemVaoCuoiMotDanhSinhVien(ListSv &l, NodeSv *p) {
	if (l.pHead == NULL) {
		l.pHead = l.pTail = p;
	}
	else {
		l.pTail->pNext = p;
		l.pTail = p;
	}
}

void XuatSinhVien(ListSv l) {
	for (NodeSv *k = l.pHead; k != NULL; k = k->pNext) {
		cout << "\nMa sinh vien: " << k->data->masv;
		cout << "\nHo: " << k->data->ho;
		cout << "\nTen: " << k->data->ten;
		cout << "\nPhai: " << k->data->phai;
		cout << "\nPassword: " << k->data->password;
		cout << "\n==================================";
	}
}

// </ DANH SACH SV ===================================================

// DANH SACH LOP ======================================================

struct lop {
	string malop;
	string tenlop;
	int n;
	Sinhvien *sv[MAXLIST];
};

typedef struct lop Lop;

struct danhsachlop {
	int n;
	Lop *Dslop[MAXLIST];
};
typedef struct danhsachlop Danhsachlop;

void Show_Danh_Sach_Lop(Danhsachlop dsl) {
	cout << "\nDANH SACH LOP";
	for (int i=0; i<dsl.n; i++) {
		cout << "\n" << i+1 << ":";
		cout << "\nMa lop: " << dsl.Dslop[i]->malop;
		cout << "\nTen lop: " << dsl.Dslop[i]->tenlop;
	}
	cout << "\n==========================";
}

int Exist_Lop(Danhsachlop &dsl, string malop) {
	for (int i=0; i<dsl.n; i++) {
		if (malop == dsl.Dslop[i]->malop) {
			return 0;
		}
	}
	return 1;
}

void Insert_Lop(Danhsachlop &dsl) {
	string n;
	dsl.Dslop[dsl.n] = new Lop;
	cout << "\nNhap ma lop: "; cin >> n;
	
	while (Exist_Lop(dsl,n) == 0) {
		cout << "\nMa lop da ton tai, vui long nhap ma so lop lai: ";
		cin >> n;
	} 
	
	dsl.Dslop[dsl.n]->malop = n;
	cin.ignore();
	cout << "\nNhap ten lop: "; getline(cin,dsl.Dslop[dsl.n]->tenlop);
	dsl.n += 1;
}

void Input_SinhVien_Lop(ListSv &l, Danhsachlop &dsl) {
	string ml;
	string msv;
	int ttlop=0;
	bool temp = true;
	while (temp) {
		cout << "\nNhap Ma lop: "; cin >> ml;
		for (int i=0; i<dsl.n; i++) {
			if (ml == dsl.Dslop[i]->malop) {
				temp = false;
				ttlop = i;
				break;
			}
		}
		if (ml != dsl.Dslop[ttlop]->malop)	cout << "\nMa lop khong ton lai, vui long nhap lai!";
	}
	temp = true;
	while (temp) {
		temp = false;
		cout << "\nNhap ma sv: "; cin >> msv;
		for (NodeSv *k = l.pHead; k!=NULL; k = k->pNext) {
			if (msv != k->data->masv) {
				temp = false;
			}
			else {
				cout << "\nMa sv da ton lai, vui long nhap lai!";
				temp = true;
				break;
			}
		}
	}
	
	NodeSv *p = KhoiTaoNodeSv(msv);
	ThemVaoCuoiMotDanhSinhVien(l,p);
	dsl.Dslop[ttlop]->sv[dsl.Dslop[ttlop]->n] = p->data;
	dsl.Dslop[ttlop]->n += 1;
}

void Show_SinhVien_Tung_Lop(ListSv &l, Danhsachlop &dsl) {
	string malop;
	bool temp = true;
	cout << "\nNhap ma lop: "; cin >> malop;
	for (int i=0; i<dsl.n; i++) {
		if (malop == dsl.Dslop[i]->malop) {
			cout << "\nMa lop: " << malop;
			cout << "\nTen lop: " << dsl.Dslop[i]->tenlop;
			cout << "\nDanh sach sinh vien: ";
			for (int j=0; j<dsl.Dslop[i]->n; j++) {
				cout << j << ": ";
				cout << dsl.Dslop[i]->sv[j]->masv << " - " <<  dsl.Dslop[i]->sv[j]->ho << " - " << dsl.Dslop[i]->sv[j]->ten << "\n";
			}
			temp = false;
			cout << "\n=============================";
		}
	}
	if (temp) {
		cout << "\nKhong co ma lop nay!";
	}
	
}

// </ DANH SACH LOP ===================================================



// QUAN LY LOP =======================================================
//
//struct lophoc {
//	Lop ttlop;
//	Sinhvien ttsv[MAXLIST];
//};
//typedef struct lophoc Lophoc;
//
//struct Quanlylophoc {
//	int n;
//	Lophoc quanlylophoc[MAXLIST];
//};
//
//void Input_SinhVien_Lop(ListSv &l, Danhsachlop &dsl, Quanlylophoc qll) {
//	int ml;
//	int msv;
//	bool temp = true;
//	while (temp) {
//		cout << "\nNhap Ma lop: "; cin >> ml;
//		for (int i=0; i<dsl.n; i++) {
//			if (ml == dsl.Dslop[i]->malop) {
//				temp = false;
//				break;
//			}
//		}
//		cout << "\nMa lop khong ton lai, vui long nhap lai!";
//	}
//	temp = true;
//	while (temp) {
//		cout << "\nNhap ma sv: "; cin >> msv;
//		for (NodeSv *k = l.pHead; k!=NULL; k = k->pNext) {
//			if (msv == k->data->masv) {
//				temp = false;
//				break;
//			}
//		}
//		cout << "\nMa sv khong ton lai, vui long nhap lai!";
//	}
//	
//}

// </ QUAN LY LOP ====================================================

// CHUC NANG =========================================================

int chucnang() {
	int n;
	cout << "\n1. Nhap lop: ";
	cout << "\n2. In danh sach lop: ";
	cout << "\n3. Nhap sinh vien cua lop: ";
	cout << "\n4. Nhap mon hoc: ";
	cout << "\n5. Xem danh sach sinh vien tung lop";
	cout << "\n6. Xem danh sach sinh vien";
	cout << "\n0. Thoat chuong trinh";
	
	cout << "\nNhap chuc nang ban chon: ";
	cin >> n; 
	
	return n;
	
}

int chucnang_sv() {
	int n;
	cout << "\n7. Thi trac nghiem: ";
	cout << "\n0. Thoat chuong trinh";
	
	cout << "\nNhap chuc nang ban chon: ";
	cin >> n; 
	
	return n;
}

// </ CHUC NANG ======================================================


// DANG NHAP =========================================================

NodeSv dangnhap(ListSv &l, string &username, string &password) {
	bool temp = true;
	NodeSv *x;
	x = new NodeSv;
	cout << "\nMoi ban nhap username va password!";
	while (temp) {
		cout << "\nUsername: "; cin >> username;
		if (username == "GV") {
			temp = false;
			break;
		}
		for (NodeSv *k = l.pHead; k != NULL; k = k->pNext) {
			if (username == k->data->masv) {
				temp = false;
				x = k;
				break;
			}
		}
		if (temp) {
			cout << "\nUsername khong ton tai, moi ban nhap lai!";
		}
	}
	temp = true;
	while (temp) {
		cout << "\nPassword: "; cin >> password;
		if (username == "GV" && password == "GV") {
			temp = false;
			break;
		}
		for (NodeSv *k = l.pHead; k != NULL; k = k->pNext) {
			if (password == k->data->password) {
				temp = false;
				x = k;
				break;
			}
		}
		if (temp) {
			cout << "\nPassword sai, moi ban nhap lai!";
		}
	}
	
	if (username == "GV") {
		cout << "\nDang nhap thanh cong, xin chao Giao vien! ";
	}
	else {
		cout << "\nDang nhap thanh cong, xin chao " << x->data->ho << " " << x->data->ten;
	}
	
	return *x;
}

// </ DANG NHAP ======================================================
int main() {
	//Khai bao
	Dsmh mh;
	Danhsachlop dsl;
	ListSv l;
	KhoiTaoListSv(l);
	int n;
	NodeSv *p;
	p = new NodeSv;
	
	// DANG NHAP
	*p = dangnhap(l, username, password);
	
	// CHUC NANG
	if (username == "GV") {
		n = chucnang();
	}
	else {
		n = chucnang_sv();
	}
	
	// MAIN
	while (n!=0) {
		if (n==1) {
			Insert_Lop(dsl);
		}
		if (n==2) {
			Show_Danh_Sach_Lop(dsl);
		}
		if (n==3) {
			Input_SinhVien_Lop(l, dsl);
		}
		if (n==5) {
			Show_SinhVien_Tung_Lop(l, dsl);
		}
		if (n==6) {
			XuatSinhVien(l);
		} 
		if (n==0) {
			break;
		}
		*p = dangnhap(l, username, password);
		if (username == "GV") {
			n = chucnang();
		}
		else {
			n = chucnang_sv();
		}
	}
	return 0;
}
