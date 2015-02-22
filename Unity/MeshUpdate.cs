using UnityEngine;
using System.Collections;
using System.Text.RegularExpressions;

public class MeshUpdate : MonoBehaviour {

	WWW lastMeshString;
	Mesh mesh;
	// Use this for initialization
	void Start () {
		lastMeshString = new WWW ("http://localhost:8080/mesh");
		mesh = GetComponent<MeshFilter> ().mesh;
		mesh.MarkDynamic ();
	}
	
	// Update is called once per frame
	void Update () {
	if (lastMeshString.isDone) {
			mesh.Clear();

			string[] lines = Regex.Split(lastMeshString.text, "\r\n|\r|\n");

			int vertexLength = int.Parse(lines[0].Split(',')[0]);
			// parse vertex length and triangle length

			int numTriangles = int.Parse(lines[0].Split(',')[1]);
			Vector3[] newVertices = new Vector3[vertexLength];

			int i = 1;
			int j = 0;

			while (lines[i].Trim() != "") {
			// parse vertices
				string[] splitline = lines[i].Split(',');
				float x = float.Parse(splitline[0]);
				float y = float.Parse(splitline[1]);
				float z = float.Parse(splitline[2]);
				newVertices[j] = new Vector3(x,y,z);
				i++;
				j++;
			}
			i++;
			j = 0;

			mesh.vertices = newVertices;

			Vector2[] newUV = new Vector2[vertexLength];
			while (lines[i].Trim() != "") {
				// parse vertices
				string[] splitline = lines[i].Split(',');
				float u = float.Parse(splitline[0]);
				float v = float.Parse(splitline[1]);
				newUV[j] = new Vector2(u,v);
				i++;
				j++;
			}

			j = 0;
			i++;

			mesh.uv = newUV;

			int[] newTriangles = new int[numTriangles * 3];
			// parse triangles
			while (j < numTriangles*3) {
				// parse vertices
				string[] splitline = lines[i].Split(',');
				newTriangles[j] = int.Parse(splitline[0]);
				newTriangles[j+1] = int.Parse(splitline[1]);
				newTriangles[j+2] = int.Parse(splitline[2]);
				i++;
				j+=3;
			}
			mesh.triangles = newTriangles;

			lastMeshString = new WWW("http://localhost:8080/mesh");
		}
	}
}
