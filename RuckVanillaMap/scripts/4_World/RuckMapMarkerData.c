class RuckMapMarkerData
{
	int Id;
	vector Pos;
	int TypeId;
	string Name;
	int ColorARGB; 

	void RuckMapMarkerData(int id = -1, vector pos = "0 0 0", int typeId = 0, string name = "", int colorARGB = 0)
	{
		Id = id;
		Pos = pos;

		SetType(typeId);
		SetName(name);

		if (colorARGB == 0)
			ColorARGB = ARGB(255, 255, 255, 255); 
		else
			ColorARGB = colorARGB;
	}

	void SetColor(int colorARGB)
	{
		ColorARGB = colorARGB;
	}

	void SetName(string name)
	{
		if (!name) name = "";
		if (name.Length() > 32)
			name = name.Substring(0, 32);

		Name = name;
	}

	void SetType(int typeId)
	{
		TypeId = typeId;
	}

	void SetPos(vector pos)
	{
		Pos = pos;
	}

	bool IsNear(vector pos, float radiusMeters)
	{
		vector a = Pos;
		vector b = pos;
		a[1] = 0;
		b[1] = 0;
		return vector.Distance(a, b) <= radiusMeters;
	}

};
