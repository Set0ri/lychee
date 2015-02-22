using UnityEngine;
using System.Collections;

public class TextureUpdater : MonoBehaviour {

	public Material stream;
	Texture2D lastTex;
	WWW lastJpegWWW;

	// Use this for initialization
	void Start () {
		lastJpegWWW = new WWW ("http://localhost:8080/frame.jpg");
		renderer.material.mainTexture = new Texture2D(4, 4, TextureFormat.DXT1, false);
	}
	
	// Update is called once per frame
	void Update () {
	if (lastJpegWWW.isDone) {
			lastTex = lastJpegWWW.texture;
			stream.mainTexture = lastTex;
			lastJpegWWW = new WWW("http://localhost:8080/frame.jpg");
		}
	}
}
