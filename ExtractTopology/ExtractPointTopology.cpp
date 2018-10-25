#include "ExtractPointTopology.h"


ExtractPointTopology::ExtractPointTopology()
{
}

ExtractPointTopology::ExtractPointTopology(vtkSmartPointer<vtkPolyData> source)
{
	this->source = source;
	size = source->GetNumberOfCells();

	triangleFilter = vtkSmartPointer<vtkTriangleFilter>::New();
	triangleFilter->SetInputData(source);
	triangleFilter->Update();
}

ExtractPointTopology::~ExtractPointTopology()
{
	source->Delete();
}

void ExtractPointTopology::SetName(string filename)
{
	this->filename = filename;
}

bool ExtractPointTopology::WriteTopology()
{
	if (_access(filename.c_str(), 0) != -1)
		if (remove(filename.c_str()) == -1)
			return false;
	ofstream file(filename, ios::app);

	for (int i = 0; i < size; i++)
	{
		list<vtkIdType> neighbors;
		GetPointNeighborIds(i, triangleFilter, neighbors);
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
