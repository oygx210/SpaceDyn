//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//
//
// Header : vertial model class to read Rainer's expression
//
// s.abiko [2007.11]
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//
#include <iostream>
using namespace std;

#include "../include/define.h"
#include "../include/common.h"

class vModel{

 public:
    
    /* Load Parameters */
    int LINKNUM, E_NUM;
    int *BB; // Link connectivity
    int *EE; // end effector

    int *Lflag; // Closed Loop flag

    int *J_type;

    Vector3 *Qi; // relative coordinate from parent to child
    Vector3 *Qe; // relative coordinate for end effector

    Vector3 *JtoC; // vector from Joint(i) to Center of Mass(i+1)
    Vector3 *CtoJ; // vector from Center of Mass(i+1) to Joint (i+1)

    Vector3 *CtoE; // vector from Center of Mass of last link to EE

    double *link_M; // mass of link
    Matrix3 *link_I; // inertia of link around Center of Mass of link w.r.t. link frame

    double *q;  // joint angle
    double *qd; // joint motion rate
    double *qdd;// joint acceleration

    Matrix3 *ORI_j; // each joint orientation matrix w.r.t. Inertia Frame
    Vector3 *POS_j; // each joint position w.r.t. Inertia Frame

    Matrix3 *ORI_e; // end-effector orientation matrix w.r.t Inerta Frame
    Vector3 *POS_e; // end-effector position w.r.t. Inertia Frame

    /*//_/_/_/     constructor of arrays      _/_/_//
    void constructor();
    void construct_ee(int E_NUM);
    
    
    //_/_/_/     destructor of arrays      _/_/_//
    void destructor();
    void destruct_ee(int E_NUM);
    */
  
	//_/_/_/     constructor of arrays      _/_/_//
	void constructor(){
      
      	BB = new int[LINKNUM];
      	EE = new int[LINKNUM];
      	Lflag = new int[LINKNUM];

      	J_type = new int[LINKNUM];
      
      	// link      
      	Qi = new Vector3[LINKNUM];
      	ORI_j = new Matrix3[LINKNUM];
      	POS_j = new Vector3[LINKNUM];

      	// link mass
      	link_M       = new double[LINKNUM];	
      	link_I       = new Matrix3[LINKNUM];
      
      	// joint
      	JtoC              = new Vector3[LINKNUM];	
      	CtoJ              = new Vector3[LINKNUM];
      
      	q                 = new double[LINKNUM];
      	qd                = new double[LINKNUM];
      	qdd               = new double[LINKNUM];

      	// spatial notation
      	S   = new Vector6[LINKNUM];
      	Xsp = new Matrix6[LINKNUM];
      	Isp = new Matrix6[LINKNUM];
      	jXc = new Matrix6[LINKNUM];
      	jXe = new Matrix6[LINKNUM];
      
      	// State values
      	Xup = new Matrix6[LINKNUM];
      	Xup_I = new Matrix6[LINKNUM];

	Qtn0 = new Vector4;
	dQtn0 = new Vector4;
      	A0 = new Matrix3;
      	POS0 = new Vector3;
      
      	v0  = new Vector3;
      	w0  = new Vector3;
      	vd0 = new Vector3;
      	wd0 = new Vector3;

      	Fe = new Vector3[LINKNUM];
      	Te = new Vector3[LINKNUM];

      	F0 = new Vector3;
      	T0 = new Vector3;

      	tau = new double[LINKNUM];
      	Force = new double[6+(LINKNUM-1)];

	}

	void construct_ee(int E_NUM){
      	Qe   = new Vector3[E_NUM+1];
     	CtoE = new Vector3[E_NUM+1];
      
      	ORI_e = new Matrix3[E_NUM+1];
      	POS_e = new Vector3[E_NUM+1];
	}
    
    
	//_/_/_/     destructor of arrays      _/_/_//
	void destructor(){
      
      	delete [] BB;
      	delete [] EE;
      	delete [] Lflag;

 	delete [] J_type;
      	
	// link
      	delete [] Qi;
	delete [] ORI_j;
     	delete [] POS_j;

        delete [] JtoC;	
        delete [] CtoJ;
      	
	delete [] S;
      	delete [] Xsp;
	delete [] Isp;
      	delete [] jXc;
      	delete [] jXe;
      
      	delete [] Xup;
	delete [] Xup_I;
	     

	// link mass
        delete [] link_M;	
        delete [] link_I;
      
      	delete [] q;
      	delete [] qd;
      	delete [] qdd;
		
        delete [] A0;
        delete [] POS0;
      
        delete [] v0;
        delete [] w0;
        delete [] vd0;
        delete [] wd0;

	delete [] F0;
      	delete [] T0;

        delete [] tau;
        delete [] Force;

	delete [] Fe;
      	delete [] Te;

	}

	void destruct_ee(int E_NUM){
    
	delete [] Qe;
	delete [] CtoE;
      
      	delete [] ORI_e;
      	delete [] POS_e;
	}

};
/*

//_/_/_/     constructor of arrays      _/_/_//
void MODEL::constructor(){
      
      BB = new int[LINKNUM];
      EE = new int[LINKNUM];
      Lflag = new int[LINKNUM];

      J_type = new int[LINKNUM];
      
      // link      
      Qi = new Vector3[LINKNUM];
      ORI_j = new Matrix3[LINKNUM];
      POS_j = new Vector3[LINKNUM];

      // link mass
      link_M       = new double[LINKNUM];	
      link_I       = new Matrix3[LINKNUM];
      
      // joint
      JtoC              = new Vector3[LINKNUM];	
      CtoJ              = new Vector3[LINKNUM];
      
      q                 = new double[LINKNUM];
      qd                = new double[LINKNUM];
      qdd               = new double[LINKNUM];

      // spatial notation
      S   = new Vector6[LINKNUM];
      Xsp = new Matrix6[LINKNUM];
      Isp = new Matrix6[LINKNUM];
      jXc = new Matrix6[LINKNUM];
      jXe = new Matrix6[LINKNUM];
      
      // State values
      Xup = new Matrix6[LINKNUM];
      Xup_I = new Matrix6[LINKNUM];

      A0 = new Matrix3;
      POS0 = new Vector3;
      
      v0  = new Vector3;
      w0  = new Vector3;
      vd0 = new Vector3;
      wd0 = new Vector3;

      Fe = new Vector3[LINKNUM];
      Te = new Vector3[LINKNUM];

      F0 = new Vector3;
      T0 = new Vector3;

      tau = new double[LINKNUM];
      Force = new double[6+(LINKNUM-1)];

}

void MODEL::construct_ee(int E_NUM){
      Qe   = new Vector3[E_NUM+1];
      CtoE = new Vector3[E_NUM+1];
      
      ORI_e = new Matrix3[E_NUM+1];
      POS_e = new Vector3[E_NUM+1];
}
    
    
//_/_/_/     destructor of arrays      _/_/_//
void MODEL::destructor(){
      
      	delete [] BB;
      	delete [] EE;
      	delete [] Lflag;

 	delete [] J_type;
      	
	// link
      	delete [] Qi;
	delete [] ORI_j;
     	delete [] POS_j;

        delete [] JtoC;	
        delete [] CtoJ;
      	
	delete [] S;
      	delete [] Xsp;
	delete [] Isp;
      	delete [] jXc;
      	delete [] jXe;
      
      	delete [] Xup;
	delete [] Xup_I;
	     

	// link mass
        delete [] link_M;	
        delete [] link_I;
      
      	delete [] q;
      	delete [] qd;
      	delete [] qdd;
		
        delete [] A0;
        delete [] POS0;
      
        delete [] v0;
        delete [] w0;
        delete [] vd0;
        delete [] wd0;

	delete [] F0;
      	delete [] T0;

        delete [] tau;
        delete [] Force;

	delete [] Fe;
      	delete [] Te;

}

void MODEL::destruct_ee(int E_NUM){
    
	delete [] Qe;
	delete [] CtoE;
      
      	delete [] ORI_e;
      	delete [] POS_e;
}
*/
// --- EOF ---
