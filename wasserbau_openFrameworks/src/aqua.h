//
//  aqua.h
//  wasserbau_3
//
//  Created by Jessica Moll on 08.06.18.
//

#ifndef aqua_h
#define aqua_h


class Aqua {
public:
    ofVec2f m_size;
    ofVec2f m_pos;
    //set(706, 1129);
    //ofVec2f m_pos.set(0, 0);
    
    void init(){
        m_size.set(706, 1129);
        m_pos.set(0, 0);
    };
};


#endif /* aqua_h */
