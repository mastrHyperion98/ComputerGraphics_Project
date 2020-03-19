# ComputerGraphics_Project
<strong>
Team #17<br>
Members: Steven Smith, Michael Rowe, Nhut Vo, Sheridan Perez Antigua<br></strong>

# Table of Contents
<ul>
 <li><a href="#description">Project Description</a>
 </li>
 <li>
  <a href="#environment">Environment Setup</a>
 </li>
 <li>
  <a href="#tools"> Tools and Libraries </a>
 </li>
 </ul>

# Project Description
<p id="description">The generation of a procedurally rendered forest implementing collision, shadows, lighting and various other computer graphics techniques to enhance the realism or artistic appreciation of the rendered scene.<br><br>
The goal of this project is to create a graphics program using OpenGLfor walking through aprocedurally created virtual world, say a forest of trees, plants, bushes,etc., or an urbancity with roads, buildings, etc. All repeating items,like the trees in the virtual forest or thebuildings  in  the virtual city, should  be  procedurally  created,  using  a  fewuser  specified parameters, if necessary. The terrain has tobe procedurally created. You are allowed to borrow digital assets for non repeating items, like a bridge, for  textures,  and  so  on,  asneeded  in  order  to  create  the virtual  world.  However  ensure  that  you  credit  the  source properly. You should have simple interactionmechanisms to navigate through the virtual world and view it from different angles. During navigation, the user must not be allowed to pass through objects.</p>

# Setup Environment

<ol id="environment">
<li>Clone or Download the repository onto your host machine.</li>
<li>Open up the Command Prompt or Unix Terminal and enter 
    <br>
    <h4>On Unix</h4><br>
    <code>cd SystemPath/ComputerGraphics_Project/ProceduralForest/Framework/vcpkg-2020-01</code>
    <br>
    <h4>On Windows</h4><br>
    <code>cd SystemPath\ComputerGraphics_Project\ProceduralForest\Framework\vcpkg-2020-01</code>
    <br>
</li>
<li> Next we need to build vcpkg for your system!<br>
    <h4>On Unix</h4><br>
    <code>./bootstrap-vcpkg.sh</code>
    <br>
     <h4>On Windows</h4><br>
    <code>.\bootstrap-vcpkg.bat</code>
    <br>
</li>
<li> Install framework libraries (may require Adminstrative privileges)
    <h4>On Unix</h4><br>
    <code>./dependencies.sh</code>
    <br>
     <h4>On Windows</h4><br>
    <code>.\dependencies.bat</code>
    <br>
</li>
<li> Add vcpkg to the CMake options
    <h4>On CLion</h4><br>
    <ul>
    <li>Launch CLion and <strong>open</strong> the project.</li>
    <li>Open settings.</li>
    <li>Navigate to the <strong>Build, Execution, Deployment</strong> option.</li>
    <li>Select the <strong> CMake </strong> option.</li>
    <li>In the text field written CMake options enter: <br>
    <code>
    -DCMAKE_TOOLCHAIN_FILE=../Framework/vcpkg-2020.01/scripts/buildsystems/vcpkg.cmake
    </code>
    </li>
    </ul>
    <br><h4>In Visual Studio 2019</h4>
     <ul>
      <li> Makes sure Visual Studio is setup for CMake <a href="https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=vs-2019">Link here</a></li>
    <li>Launch Visual Studio and <strong>open</strong> the project directory.</li>
    <li>Open the GUI of the CMakeSettings.json or follow these instructions <a href="https://docs.microsoft.com/en-us/cpp/build/customize-cmake-settings?view=vs-2019">Link Here!</a></li>
    <li>Find the CMake Toolchain File option</li>
    <li>Use the file explorer option to add the <code>../Framework/vcpkg-2020.01/scripts/buildsystems/vcpkg.cmake</code> file as toolchain file.</li>
    <li>In the text field written CMake options enter: <br>
    </ul>
</li>
</ol>

<p id="tools"></p>

# Tools and Libraries

<table>
    <caption> Project Tools and Libraries </caption>
    <tr>
        <th>Name</th>
        <th>Version</th>
    </tr>
    <tr>
        <td>GCC</td>
        <td>9.20</td>
    </tr>
    <tr>
     <td>CMake</td>
     <td>3.15.3</td>
    </tr>
 <tr>
  <td>GLFW3</td>
  <td>3.3.2-1</td>
 </tr>
 <td>vcpkg</td>
 <td>2020.01</td>
  </tr>
 <td>glew</td>
 <td>2.1.0-1</td>
  </tr>
 <td>glm</td>
 <td>0.9.9.7-1</td>
 </tr>
 <td>stb_image</td>
 <td>2.25</td>
 
</table>
