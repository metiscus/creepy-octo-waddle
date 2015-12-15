#ifndef SAMPLER_H_INCLUDED
#define SAMPLER_H_INCLUDED

class Sampler
{
public:
    Sampler();
    Sampler(const Sampler&) = delete;
    ~Sampler();
    
    Sampler& operator=(const Sampler&) = delete;
    
    void Bind(int unit);
    
private:
    unsigned int unit_;
    unsigned int sampler_;
    
    friend class Uniform;
};

#endif /* SAMPLER_H_INCLUDED */
