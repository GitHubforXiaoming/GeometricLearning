#pragma once
#include "ExtractTopology.h"
class ExtractCellTopology :
	public ExtractTopology
{
private:
	int size;
	string filename;
	vtkSmartPointer<vtkPolyData> source;
	vtkSmartPointer<vtkTriangleFilter> triangleFilter;
public:
	ExtractCellTopology();
	ExtractCellTopology(vtkSmartPointer<vtkPolyData> source);
	virtual ~ExtractCellTopology();

	void SetName(string filename);
	bool WriteTopology();
};

