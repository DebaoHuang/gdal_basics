#include <iostream>
#include <fstream>
#include <gdal_priv.h>
#include <boost/filesystem.hpp>
//#include <io.h>

#define outputfile "C:/Users/Debao/Desktop/IndividualStudy/Debao/result.txt"

using namespace std;
using namespace boost::filesystem;

/* old approach
void getfilename(vector<string>& filename, char* addr)
{
	long long Handle;
	struct _finddata_t FileInfo;
	Handle = _findfirst(addr, &FileInfo);
	if (Handle != -1)
	{
		do {
			filename.push_back(FileInfo.name);
		} while (_findnext(Handle, &FileInfo) == 0);
	}
	_findclose(Handle);
}
*/

void getfilename(string addr, vector<string>& filename)
{
	path input = addr;
	recursive_directory_iterator it(input);
	recursive_directory_iterator endit;
	while (it != endit)
	{
		if (it->path().extension() == ".TIF")
		{
			string file_name = it->path().string();
			filename.push_back(file_name);
		}
		it++;
	}
}

int main(int argc, char* argv[])
{
	std::ofstream outfile;
	outfile.open(outputfile);

	cout << "Start to get filenames of all *.tif files." << endl;
	vector <string> filename;
	string root = argv[1];
	//getfilename(filename, targetfile);
	getfilename(root, filename);
	cout << "All filenames of *.tif files' has been collected." << endl;

	cout << "Start to read the *.tif files and get information." << endl;
	GDALDataset* Img;
	GDALAllRegister();

	for (int j = 0; j < filename.size(); j++)
	{
		//string file = filename[j];
		//char tmp[100];
		//strcpy_s(tmp, argv[1]);
		//strcat_s(tmp, file.c_str());

		Img = (GDALDataset*)GDALOpen(filename[j].c_str(), GA_ReadOnly);

		int nCols = Img->GetRasterXSize();
		int nRows = Img->GetRasterYSize();
		int nBands = Img->GetRasterCount();

		outfile << "for " << filename[j] << ", " << endl;
		outfile << "raster size: ";
		outfile << nCols << '*' << nRows << endl;
		outfile << "number of bands: ";
		outfile << nBands << endl;

		int bApproxOK = false;
		int bForce = true;
		double pdfMin, pdfMax, pdfMean, pdfStdDev;

		for (int i = 1; i <= nBands; i++)
		{
			GDALRasterBand* pBand = Img->GetRasterBand(i);
			pBand->GetStatistics(bApproxOK, bForce, &pdfMin, &pdfMax, &pdfMean, &pdfStdDev);
			outfile << "for band " << i << ", the mean and standard deviation are: ";
			outfile << pdfMean << ' ' << pdfStdDev << endl;
		}
	}
	std::cout << "All the information has been writen into " << outputfile << endl;

	outfile.close();
	GDALClose((GDALDataset*)Img);

	return 0;
}

