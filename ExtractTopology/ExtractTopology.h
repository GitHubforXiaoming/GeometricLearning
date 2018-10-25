#pragma once

#include "io.h"

#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSTLReader.h>
#include <vtkTriangleFilter.h>

#include <list>
#include <set>

using namespace std;

class ExtractTopology
{
public:
	ExtractTopology();
	virtual ~ExtractTopology();

	virtual bool WriteTopology() { return true;  }
	virtual void SetName(string filename) {}

	void GetCellNeighborIds(vtkIdType cellId, vtkSmartPointer<vtkTriangleFilter> triangleFilter, list<vtkIdType>& neighbors);

	void GetPointNeighborIds(vtkIdType pointId, vtkSmartPointer<vtkTriangleFilter> triangleFilter, list<vtkIdType>& neighbors);
};

