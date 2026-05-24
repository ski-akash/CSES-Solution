class Solution {
public:
    vector<long long> st,lz;
    int n;

    void build(int node, int l, int r, vector<int> &nums){
        // base case ::
        if(l == r){
            st[node] = nums[l];
            return;
        }

        int mid = l + (r-l)/2;

        build(2*node+1,l,mid,nums);
        build(2*node+2,mid+1,r,nums);

        st[node] = st[2*node+1] + st[2*node+2];
    }

    void push(int node, int l, int r){
        if(lz[node] == 1){
            st[node] = (r-l+1) - st[node];

            if(l != r){
                lz[2*node+1] ^= 1;
                lz[2*node+2] ^= 1;
            }

            lz[node] = 0;
        }
    }

    int query(int node, int l, int r, int L, int R){
        push(node,l,r);

        // NO Overlap ::
        if(r < L || R < l) return 0; 

        // Complete Overlap ::
        if(L <= l && r <= R) return st[node];

        // Parital Overlap ::
        int mid = l + (r-l)/2;
        int l_sum = query(2*node+1,l,mid,L,R);
        int r_sum = query(2*node+2,mid+1,r,L,R);

        return l_sum + r_sum;
    }

    void update(int node, int l, int r, int L, int R){
        push(node,l,r);

        // NO Overlap ::
        if(r < L || R < l) return; 

        // Complete Overlap ::
        if(L <= l && r <= R){
            lz[node] = 1;
            push(node,l,r);
            return;
        }

        // Parital Overlap ::
        int mid = l + (r-l)/2;
        update(2*node+1,l,mid,L,R);
        update(2*node+2,mid+1,r,L,R);

        st[node] = st[2*node+1] + st[2*node+2];
    }

    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
            
        n = nums1.size();
        st.resize(4*n,0);
        lz.resize(4*n,0);

        build(0,0,n-1,nums1);

        long long sum = 0;
        for(int elem : nums2) sum += elem;

        vector<long long> ans;
        for(auto q : queries){
            if(q[0] == 1){
                int l = q[1], r = q[2];
                update(0,0,n-1,l,r);
            }
            else if(q[0] == 2){
                int p = q[1];
                sum = sum + (1LL) * p * query(0,0,n-1,0,n-1);
            }
            else ans.push_back(sum);
        }
        
        return ans;
    }
};