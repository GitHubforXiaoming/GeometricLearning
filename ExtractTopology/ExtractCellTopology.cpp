#include "ExtractCellTopology.h"


ExtractCellTopology::ExtractCellTopology()
{
}

ExtractCellTopology::ExtractCellTopology(vtkSmartPointer<vtkPolyData> source)
{
	this->source = source;
	size = source->GetNumberOfCells();

	triangleFilter = vtkSmartPointer<vtkTriangleFilter>::New();
	triangleFilter->SetInputData(source);
	triangleFilter->Update();
}

ExtractCellTopology::~ExtractCellTopology()
{
	source->Delete();
}

void ExtractCellTopology::SetName(string filename)
{
	this->filename = filename;
}

bool ExtractCellTopology::WriteTopology()
{
	if (_access(filename.c_str(), 0) != -1)
		if (remove(filename.c_str()) == -1)
			return false;
	ofstream file(filename, ios::app);

	for (int i = 0; i < size; i++) 
	{
		list<vtkIdType> neighbors;
		GetCellNeighborIds(i, triangleFilter, neighbors);
		for (auto neighbor : neighbors)
		{
			file << neighbor << " ";
		}
		if (i < size - 1)
			file << endl;
	}
	file.close();
	return true;
}