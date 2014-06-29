#ifndef _KEYVALUEPAIR_
#define _KEYVALUEPAIR_

/**
 * A container for a string key and a value.
 */
template <class T> class KeyValuePair{
public:
    /** Generic Value. */
    T* value;
    /** String key. */
    char* key;

    KeyValuePair(){
        value = 0;
        key = 0;
    }

    /**
     * Find value in the given sorted KeyValuePair array.
     * Implementation uses a binary search so list must be sorted by key.
     */
    static T* findValue(KeyValuePair<T>* list, unsigned short listSize, const char* key){
        int max = listSize;
        int min = 0;
        while(max >= min){
            int mid = (max+min)/2;
            int comp = strcmp(key, list[mid].key);

            if(comp == 0){ //Found value.
                return list[mid].value;
            }else if(comp > 0){
                min = mid+1;
            }else if(comp < 0){
                max = mid-1;
            }
        
        }
        return 0;
    }

    /**
     * Insert value and key into given KeyValuePair array.
     * Assumes array is not full, and implemented.
     * Performs a sorted insert.
     */
    static void insertSort(T* value, char* key, KeyValuePair<T>* list,const int size){
        //Find empty spot to insert into.
        for(int i = 0; i < size; i++){
            if(list[i].key == 0){

                list[i].key = key;
                list[i].value = value;

                //Find proper key order.
                int current = i;
                for(int j = i-1; j >= 0; j--){
                    if(strcmp(list[current].key, list[j].key) < 0){

                        //Shift down.
                        char* tmpName = list[j].key;
                        T* tmpValue = list[j].value;
                        list[j].key = list[current].key;
                        list[j].value = list[current].value;

                        list[current].key = tmpName;
                        list[current].value = tmpValue;

                        current--;
                    }else{
                        break;
                    }
                }

                break;
            }
        }
    }

};

#endif