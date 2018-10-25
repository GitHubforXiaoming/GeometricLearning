#include "ExtractCellTopology.h"
#include "ExtractPointTopology.h"

vtkSmartPointer<vtkPolyData> LoadData(const char* filename)
{
	vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
	reader->SetFileName(filename);
	reader->Update();
	return reader->GetOutput();
}

ExtractTopology* ParseCommandLine(int argc, char** argv)
{
	ExtractTopology* extract = NULL;
	if (argc == 3)
	{
		vtkSmartPointer<vtkPolyData> source = LoadData(argv[2]);
		string name = string(argv[2]);
		name = name.substr(0, name.length() - 4);
		name += string(argv[1]) + ".txt";
		if (string(argv[1]) == "-cell")
		{
			extract = new ExtractCellTopology(source);
			extract->SetName(name);
		} 
		else if (string(argv[1]) == "-point")
		{
			extract = new ExtractCellTopology(source);
			extract->SetName(name);
		}
	}

	return extract;
}

int main(int argc, char* argv[])
{
	ExtractTopology* extract = ParseCommandLine(argc, argv);
	if (extract != NULL)
	{
		extract->WriteTopology();
	}
	return 0;
}