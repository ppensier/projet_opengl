#include "minitab.h"
#include "simpleViewer.h"

using namespace std;

MiniTab::MiniTab()
{

}


MiniTab::MiniTab(QVector<QVector3D>& vector) :
Viewer(m_vector, m_coordInterp, distanceTir, vertices_by_x)
{
    //m_vector(vector);
    for (int i=0; i<vector.length(); i++)
    {
        m_vector.append(vector[i]);
    }
}


void MiniTab::computeIntervisility()
{
    cout << "on rentre ici!" << endl;
    for (int i(0); i<m_vector.length()-vertices_by_x-1; i++)
    {
        float distance = m_coordInterp[0].distanceToPoint(m_vector[i]);

        if (distance <= distanceTir && intervisibility(m_coordInterp[0],m_vector[i]))
        {
            m_vect1.append(m_vector[i]);
        }
    }
    cout << "SIZE: " << m_vect1.length() << endl;
}
