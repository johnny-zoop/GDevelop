/** \file
 *  Game Develop
 *  2008-2011 Florian Rival (Florian.Rival@gmail.com)
 */

#include <vector>
#include <string>
#include "GDL/Object.h"
#include <cmath>
#include "GDL/aTime.h"
#include "GDL/Event.h"
#include <iostream>
#include <sstream>
#include "GDL/Chercher.h"
#include "GDL/CommonTools.h"
#include "GDL/Force.h"
#include <iostream>

#include "GDL/RuntimeScene.h"
#include "GDL/ManualTimer.h"


////////////////////////////////////////////////////////////
/// Remise � z�ro d'un timer ( et cr�ation de celui ci si il n'existe pas )
///
/// Type : ResetTimer
/// Param�tre 1 : Nom du timer
////////////////////////////////////////////////////////////
bool ActResetTimer( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & action )
{
    string timerName = action.GetParameter(0).GetAsTextExpressionResult(scene, objectsConcerned);
    if ( timerName == "" ) return false;

    //Le timer existe il ? on parcourt la liste.
    for ( unsigned int i = 0;i < scene.timers.size();i++ )
    {
        //On cherche le nom du timer
        if ( scene.timers[i].GetName() == timerName )
        {
            //On l'a trouv� !
            scene.timers[i].Reset();
            return true;
        }
    }

    //Il n'existe pas, on l'ajoute
    scene.timers.push_back( ManualTimer(timerName) );

    return true;
}

////////////////////////////////////////////////////////////
/// Mise en pause d'un timer
///
/// Type : PauseTimer
/// Param�tre 1 : Nom du timer
////////////////////////////////////////////////////////////
bool ActPauseTimer( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & action )
{
    string timerName = action.GetParameter(0).GetAsTextExpressionResult(scene, objectsConcerned);
    if ( timerName == "" ) return false;

    //Le timer existe il ? on parcourt la liste.
    for ( unsigned int i = 0;i < scene.timers.size();i++ )
    {
        //On cherche le nom du timer
        if ( scene.timers[i].GetName() == timerName )
        {
            //On l'a trouv� !
            scene.timers[i].SetPaused(true);
            return true;
        }
    }

    //Il n'existe pas, on l'ajoute
    scene.timers.push_back( ManualTimer(timerName) );
    scene.timers.back().SetPaused(true);

    return true;
}

////////////////////////////////////////////////////////////
/// Enl�ve la pause d'un timer
///
/// Type : UnPauseTimer
/// Param�tre 1 : Nom du timer
////////////////////////////////////////////////////////////
bool ActUnPauseTimer( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & action )
{
    string timerName = action.GetParameter(0).GetAsTextExpressionResult(scene, objectsConcerned);
    if ( timerName == "" ) return false;

    //Le timer existe il ? on parcourt la liste.
    for ( unsigned int i = 0;i < scene.timers.size();i++ )
    {
        //On cherche le nom du timer
        if ( scene.timers[i].GetName() == timerName )
        {
            //On l'a trouv� !
            scene.timers[i].SetPaused(false);
            return true;
        }
    }

    //Il n'existe pas, on l'ajoute
    scene.timers.push_back( ManualTimer(timerName) );
    scene.timers.back().SetPaused(false);

    return true;
}

////////////////////////////////////////////////////////////
/// Modifier l'�chelle du temps
///
/// Type : ChangeTimeScale
/// Param�tre 1 : Nouvelle �chelle du temps
////////////////////////////////////////////////////////////
bool ActChangeTimeScale( RuntimeScene & scene, ObjectsConcerned & objectsConcerned, const Instruction & action )
{
    scene.SetTimeScale(action.GetParameter( 0 ).GetAsMathExpressionResult(scene, objectsConcerned));

    return true;
}
