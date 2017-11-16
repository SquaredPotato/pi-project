#ifndef COLUMN_I2CDEVICE_H
#define COLUMN_I2CDEVICE_H

#include <cstddef>
#include <boost/serialization/access.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>

class I2CDevice {
public:
    I2CDevice();

    virtual void init(int id);
    int send(const void *data, size_t size);
    int writeReg8(int reg, int data);
    int readReg8(int reg);
    int readReg16(int reg);

private:
    int id;
protected:
    int handle;

	//for saving
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, unsigned int version)
	{
		ar  & boost::serialization::make_nvp("id", id)
			& boost::serialization::make_nvp("handle", handle);
	}
};


#endif //COLUMN_I2CDEVICE_H

