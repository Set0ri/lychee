import base64
import cherrypy

globals()['lastjpeg'] = ''
globals()['lastmesh'] = ''

class WebApp:
 @cherrypy.expose
 def upload(self, data = None):
  globals()['lastjpeg'] = base64.b64decode(data)
  return 'yo'

 @cherrypy.expose
 def frame_jpg(self):
  cherrypy.response.headers['Content-Type'] = 'image/jpeg'
  return globals()['lastjpeg'] 

 @cherrypy.expose
 def update(self, data):
  globals()['lastmesh'] = data
  return 'yo'

 @cherrypy.expose
 def mesh(self):
  return globals()['lastmesh']

if __name__ == '__main__':
 cherrypy.quickstart(WebApp())

