namespace std {
    template <>
    struct hash<Student> {
        size_t operator()(const Student &s) const {
            return std::hash<std::string>()(s.get_projectRole()) ^ hash<std::string>()(s.get_name());
        }
    };
}

bool sort_by_groupNumber(const Student s1, const Student s2);
bool sort_by_projectRole(const Student s1, const Student s2);
bool sort_by_workRating(const Student s1, const Student s2);
bool sort_by_commRating(const Student s1, const Student s2);


#endif
