#pragma once
#include "ExtractTopology.h"
class ExtractPointTopology :
	public ExtractTopology
{
private:
	int size;
	string filename;
	vtkSmartPointer<vtkPolyData> source;
	vtkSmartPointer<vtkTriangleFilter> triangleFilter;
public:
	ExtractPointTopology();
	ExtractPointTopology(vtkSmartPointer<vtkPolyData> source);
	virtual ~ExtractPointTopology();

	void SetName(string filename);
	bool WriteTopology();
};

