#ifndef __TEXTURE_H_
#define __TEXTURE_H_
class texture {
public:
    texture(){};
    virtual ~texture(){}

    unsigned int id(){ return m_id; }

private:
    unsigned int m_id;
};


#endif // __TEXTURE_H_
