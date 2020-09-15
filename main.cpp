#include <iostream>
#include <fstream>
#include<io.h>
#include<gdal_priv.h>

using namespace std;

int main()
{
	ofstream outfile;
	outfile.open("C:/Users/Debao/Desktop/project1/result.txt");
	GDALDataset* Img;
	GDALAllRegister();
	char* addr = "C://Users//Debao//Desktop//Color_Balancing//DATA//img_rpc_BA//*.tif";
	long long Handle;
	struct _finddata_t FileInfo;
	Handle = _findfirst(addr, &FileInfo);
	vector <string> filename;
	if (Handle != -1)
	{
		do {
			filename.push_back(FileInfo.name);
		} while (_findnext(Handle, &FileInfo) == 0);
	}
	_findclose(Handle);

	for (int j = 0; j < filename.size(); j++)
	{
		string file = filename[j];
		char tmp[100];
		strcpy(tmp, "C:/Users/Debao/Desktop/Color_Balancing/DATA/img_rpc_BA/");
		strcat(tmp, file.c_str());
		Img = (GDALDataset*)GDALOpen(tmp, GA_ReadOnly);
		int nCols = Img->GetRasterXSize();
		int nRows = Img->GetRasterYSize();
		int nBands = Img->GetRasterCount();
		cout << "for " << file << ", " << endl;
		outfile << "for " << file << ", " << endl;
		cout << "raster size: ";
		outfile << "raster size: ";
		cout << nCols << '*' << nRows << endl;
		outfile << nCols << '*' << nRows << endl;
		cout << "number of bands: ";
		outfile << "number of bands: ";
		cout << nBands << endl;
		outfile << nBands << endl;
		int bApproxOK = false;
		int bForce = true;
		double pdfMin, pdfMax, pdfMean, pdfStdDev;
		for (int i = 1; i <= nBands; i++)
		{
			GDALRasterBand* pBand = Img->GetRasterBand(i);
			pBand->GetStatistics(bApproxOK, bForce, &pdfMin, &pdfMax, &pdfMean, &pdfStdDev);
			cout << "for band " << i << ", the mean and standard deviation are: ";
			outfile << "for band " << i << ", the mean and standard deviation are: ";
			cout << pdfMean << ' ' << pdfStdDev << endl;
			outfile << pdfMean << ' ' << pdfStdDev << endl;
		}
	}
	outfile.close();
	return 0;
}