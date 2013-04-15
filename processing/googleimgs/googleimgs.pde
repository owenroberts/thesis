
import java.net.HttpURLConnection;    // required for HTML download
import java.net.URL;
import java.net.URLEncoder;
import java.io.InputStreamReader;     // used to get our raw HTML source        

/*
GET GOOGLE IMAGE SEARCH URLs
 Jeff Thompson | 2013 | www.jeffreythompson.org
 
 Retrieves full image URLs from a Google image search (which can then be downloaded via PImage's
 'loadImage' method.
 
 The main download method used here is built on PhyloWidget, since Processing's usual 'loadStrings'
 returns a HTTP 403 error:
 http://code.google.com/p/phylowidget/source/browse/trunk/PhyloWidget/src/org/phylowidget/render/images/ImageSearcher.java
 
 Other arguments (some working, some not) via:
 https://developers.google.com/image-search/v1/jsondevguide#json_args
 
 Also looks helpful:
 https://developers.google.com/custom-search/docs/xml_results?hl=en
 
 */






String searchTerm = "french toast";   // term to search for (use spaces to separate terms)
int offset = 20;                      // we can only 20 results at a time - use this to offset and get more!
PImage[] imgs = new PImage[offset];
String fileSize = ".1mp";             // specify file size in mexapixels (S/M/L not figured out yet)
String source = null;                 // string to save raw HTML source code
int counter = 0;

void setup() {
  size(800, 400);
  background(0);
}
void draw() {
  //background(0);
  // format spaces in URL to avoid problems
  searchTerm = searchTerm.replaceAll(" ", "%20");

  // get Google image search HTML source code; mostly built from PhyloWidget example:
  // http://code.google.com/p/phylowidget/source/browse/trunk/PhyloWidget/src/org/phylowidget/render/images/ImageSearcher.java
  try {
    URL query = new URL("http://images.google.com/images?gbv=1&start=" + counter + "&q=" + searchTerm + "&tbs=isz:lt,islt:" + fileSize);
    HttpURLConnection urlc = (HttpURLConnection) query.openConnection();                                // start connection...
    urlc.setInstanceFollowRedirects(true);
    urlc.setRequestProperty("User-Agent", "");
    urlc.connect();
    BufferedReader in = new BufferedReader(new InputStreamReader(urlc.getInputStream()));               // stream in HTTP source to file
    StringBuffer response = new StringBuffer();
    char[] buffer = new char[1024];
    while (true) {
      int charsRead = in.read(buffer);
      if (charsRead == -1) {
        break;
      }
      response.append(buffer, 0, charsRead);
    }
    in.close();                                                                                          // close input stream (also closes network connection)
    source = response.toString();
  }
  // any problems connecting? let us know
  catch (Exception e) {
    e.printStackTrace();
  }

  // print full source code (for debugging)
  // println(source);

  // extract image URLs only, starting with 'imgurl'
  if (source != null) {
    // built partially from: http://www.mkyong.com/regular-expressions/how-to-validate-image-file-extension-with-regular-expression
    String[][] m = matchAll(source, "imgurl=(.*?\\.(?i)(jpg|jpeg|png|gif))");    // (?i) means case-insensitive

      String url = m[0][1];
    imgs[counter] = loadImage(url);
    if (imgs[counter] != null) 
      image(imgs[counter], random(width), random(height), 100, 100);
  }
  if (counter == 19) {
    counter = 0;
  } else {
    counter++;
  }
  println(counter);
}

// ** here we get the 2nd item from each match - this is our 'group' containing just the file URL and extension

