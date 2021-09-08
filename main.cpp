#include <iostream>
#include <vector>


    


int main()
{
    int N;
    
    cout << "Please Enter Number of classes: ";
    cin >> N;
    

    
    vector<string> store(N);
    
    for (int i = 0; i < N; i++)
    {
        cout << "Class #" << i+1 << " ";
        cin >> store[i];
    }
    
    cout << "\n\nHere are the classes:\n";
    for (size_t i=0; i<store.size(); ++i)
    {
        cout << store[i] << '\t';
    }
    
    
    
    return 0;
}
