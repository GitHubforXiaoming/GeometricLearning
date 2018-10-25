#include "ExtractTopology.h"


ExtractTopology::ExtractTopology()
{
}


ExtractTopology::~ExtractTopology()
{
}

void ExtractTopology::GetCellNeighborIds(vtkIdType cellId, vtkSmartPointer<vtkTriangleFilter> triangleFilter, list<vtkIdType>& neighbors)
{
	vtkSmartPointer<vtkIdList> cellPointIds = vtkSmartPointer<vtkIdList>::New();
	triangleFilter->GetOutput()->GetCellPoints(cellId, cellPointIds);

	for (vtkIdType i = 0; i < cellPointIds->GetNumberOfIds(); i++)
	{
		vtkSmartPointer<vtkIdList> idList =
			vtkSmartPointer<vtkIdList>::New();

		//add one of the edge points
		idList->InsertNextId(cellPointIds->GetId(i));

		//add the other edge point
		if (i + 1 == cellPointIds->GetNumberOfIds())
		{
			idList->InsertNextId(cellPointIds->GetId(0));
		}
		else
		{
			idList->InsertNextId(cellPointIds->GetId(i + 1));
		}
		//get the neighbors of the cell
		vtkSmartPointer<vtkIdList> neighborCellIds =
			vtkSmartPointer<vtkIdList>::New();

		triangleFilter->GetOutput()->GetCellNeighbors(cellId, idList, neighborCellIds);

		for (vtkIdType j = 0; j < neighborCellIds->GetNumberOfIds(); j++)
		{
			neighbors.push_back(neighborCellIds->GetId(j));
		}
	}
}

void ExtractTopology::GetPointNeighborIds(vtkIdType pointId, vtkSmartPointer<vtkTriangleFilter> triangleFilter, list<vtkIdType>& neighbors)
{
	set<vtkIdType> neis;
	vtkSmartPointer<vtkIdList> cellIdList = vtkSmartPointer<vtkIdList>::New();
	//get all cells that vertex 'id' is a part of
	triangleFilter->GetOutput()->GetPointCells(pointId, cellIdList);

	for (vtkIdType i = 0; i < cellIdList->GetNumberOfIds(); i++)
	{
		vtkSmartPointer<vtkIdList> pointIdList = vtkSmartPointer<vtkIdList>::New();
		triangleFilter->GetOutput()->GetCellPoints(cellIdList->GetId(i), pointIdList);
		for (vtkIdType j = 0; j < pointIdList->GetNumberOfIds(); j++)
			if (pointIdList->GetId(j) != pointId)
				neis.insert(pointIdList->GetId(j));
	}
	for (auto id : neis)
		neighbors.push_back(id);
}