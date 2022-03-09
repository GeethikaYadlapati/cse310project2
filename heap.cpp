void max_heapify(SOC *arr, int n, int i, string literal);
void buildHeap(SOC *arr, int n, string literal);
SOC deleteMax(SOC *arr, int *n, string literal);

void max_heapify(SOC *arr, int n, int i, string literal)

{

 int largest = i; // Initialize largest as root


    int l = 2 * i + 1; // left = 2*i + 1

    int r = 2 * i + 2; // right = 2*i + 2



    // If left child is larger than root

    if (l < n && getNumberOfWorkers(arr[l],literal) > getNumberOfWorkers(arr[largest],literal))
    {
        largest = l;
        //cout << "arr[l].male=" << arr[l].male << "arr[largest]2=" << l << "-" << largest << "-" << arr[largest].occupation << "-" << arr[largest].male << "\n";
    }


    // If right child is larger than largest so far

    if (r < n && getNumberOfWorkers(arr[r],literal) > getNumberOfWorkers(arr[largest],literal))
    {
        largest = r;
        //cout << "arr[r].male=" << arr[r].male << "arr[largest]3=" << n << "N-" << r << "R-"<< largest << "largest-" << arr[largest].occupation << "-" << arr[largest].male << "\n";
    }

    //cout << "arr[largest]=" << i << "-" << largest << "-" << arr[largest].occupation << "-" << arr[largest].male << "\n";


    // If largest is not root

    if (largest != i) {

        swap(arr[i], arr[largest]);



        // Recursively heapify the affected sub-tree

        max_heapify(arr, n, largest, literal);

    }

}

void buildHeap(SOC *arr, int n, string literal)
{
    //cout << n << "\n";
    // Index of last non-leaf node
	//cout << "n=" << n << "\n";
    int startIdx = (n / 2) - 1;

    // Perform reverse level order traversal
    // from last non-leaf node and heapify
    // each node
    for (int i = startIdx; i >= 0; i--) {
    	//cout << "i=" << i << "\n";
        max_heapify(arr, n, i, literal);
    }
}

// Function to delete the root from Heap

SOC deleteMax(SOC *arr, int *n, string literal)

{

	int original = *n;
	swap(arr[0], arr[*n - 1]);
    //SOC originalRoot = arr[0];

    // Get the last element

    //SOC lastElement = arr[n - 1];



    // Replace root with last element

    //arr[0] = lastElement;



    // Decrease size of heap by 1

    *n = *n - 1;



    // heapify the root node

    max_heapify(arr, *n, 0, literal);



return arr[original-1];

}